"""engine.SCons.Tool.msvc

Tool-specific initialization for Microsoft Visual C/C++.

There normally shouldn't be any need to import this module directly.
It will usually be imported through the generic SCons.Tool.Tool()
selection method.

"""

#
# Copyright (c) 2001, 2002, 2003, 2004 The SCons Foundation
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
# KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

__revision__ = "/home/scons/scons/branch.0/branch.96/baseline/src/engine/SCons/Tool/msvc.py 0.96.1.D001 2004/08/23 09:55:29 knight"

import os.path
import re
import string

import SCons.Action
import SCons.Builder
import SCons.Errors
import SCons.Platform.win32
import SCons.Tool
import SCons.Tool.msvs
import SCons.Util
import SCons.Warnings

CSuffixes = ['.c', '.C']
CXXSuffixes = ['.cc', '.cpp', '.cxx', '.c++', '.C++']

def _parse_msvc7_overrides(version):
    """ Parse any overridden defaults for MSVS directory locations in MSVS .NET. """

    # First, we get the shell folder for this user:
    if not SCons.Util.can_read_reg:
        raise SCons.Errors.InternalError, "No Windows registry module was found"

    comps = ""
    try:
        (comps, t) = SCons.Util.RegGetValue(SCons.Util.HKEY_CURRENT_USER,
                                            r'Software\Microsoft\Windows\CurrentVersion' +\
                                            r'\Explorer\Shell Folders\Local AppData')
    except SCons.Util.RegError:
        raise SCons.Errors.InternalError, "The Local AppData directory was not found in the registry."

    comps = comps + '\\Microsoft\\VisualStudio\\' + version + '\\VCComponents.dat'
    dirs = {}

    if os.path.exists(comps):
        # now we parse the directories from this file, if it exists.
        # We only look for entries after: [VC\VC_OBJECTS_PLATFORM_INFO\Win32\Directories],
        # since this file could contain a number of things...
        f = open(comps,'r')
        line = f.readline()
        found = 0
        while line:
            line.strip()
            if line.find(r'[VC\VC_OBJECTS_PLATFORM_INFO\Win32\Directories]') >= 0:
                found = 1
            elif line == '' or line[:1] == '[':
                found = 0
            elif found == 1:
                kv = line.split('=', 1)
                if len(kv) == 2:
                    (key, val) = kv
                key = key.replace(' Dirs','')
                dirs[key.upper()] = val
            line = f.readline()
        f.close()
    else:
        # since the file didn't exist, we have only the defaults in
        # the registry to work with.
        try:
            K = 'SOFTWARE\\Microsoft\\VisualStudio\\' + version
            K = K + r'\VC\VC_OBJECTS_PLATFORM_INFO\Win32\Directories'
            k = SCons.Util.RegOpenKeyEx(SCons.Util.HKEY_LOCAL_MACHINE,K)
            i = 0
            while 1:
                try:
                    (key,val,t) = SCons.Util.RegEnumValue(k,i)
                    key = key.replace(' Dirs','')
                    dirs[key.upper()] = val
                    i = i + 1
                except SCons.Util.RegError:
                    break
        except SCons.Util.RegError:
            # if we got here, then we didn't find the registry entries:
            raise SCons.Errors.InternalError, "Unable to find MSVC paths in the registry."
    return dirs

def _get_msvc7_path(path, version, platform):
    """
    Get Visual Studio directories from version 7 (MSVS .NET)
    (it has a different registry structure than versions before it)
    """
    # first, look for a customization of the default values in the
    # registry: These are sometimes stored in the Local Settings area
    # for Visual Studio, in a file, so we have to parse it.
    dirs = _parse_msvc7_overrides(version)

    if dirs.has_key(path):
        p = dirs[path]
    else:
        raise SCons.Errors.InternalError, "Unable to retrieve the %s path from MS VC++."%path

    # collect some useful information for later expansions...
    paths = SCons.Tool.msvs.get_msvs_install_dirs(version)

    # expand the directory path variables that we support.  If there
    # is a variable we don't support, then replace that entry with
    # "---Unknown Location VSInstallDir---" or something similar, to clue
    # people in that we didn't find something, and so env expansion doesn't
    # do weird things with the $(xxx)'s
    s = re.compile('\$\(([a-zA-Z0-9_]+?)\)')

    def repl(match, paths=paths):
        key = string.upper(match.group(1))
        if paths.has_key(key):
            return paths[key]
        else:
            return '---Unknown Location %s---' % match.group()

    rv = []
    for entry in p.split(os.pathsep):
        entry = s.sub(repl,entry)
        rv.append(entry)

    return string.join(rv,os.pathsep)

def get_msvc_path (path, version, platform='x86'):
    """
    Get a list of visualstudio directories (include, lib or path).  Return
    a string delimited by ';'. An exception will be raised if unable to
    access the registry or appropriate registry keys not found.
    """

    if not SCons.Util.can_read_reg:
        raise SCons.Errors.InternalError, "No Windows registry module was found"

    # normalize the case for comparisons (since the registry is case
    # insensitive)
    path = string.upper(path)

    if path=='LIB':
        path= 'LIBRARY'

    if float(version) >= 7.0:
        return _get_msvc7_path(path, version, platform)

    path = string.upper(path + ' Dirs')
    K = ('Software\\Microsoft\\Devstudio\\%s\\' +
         'Build System\\Components\\Platforms\\Win32 (%s)\\Directories') % \
        (version,platform)
    for base in (SCons.Util.HKEY_CURRENT_USER,
                 SCons.Util.HKEY_LOCAL_MACHINE):
        try:
            k = SCons.Util.RegOpenKeyEx(base,K)
            i = 0
            while 1:
                try:
                    (p,v,t) = SCons.Util.RegEnumValue(k,i)
                    if string.upper(p) == path:
                        return v
                    i = i + 1
                except SCons.Util.RegError:
                    break
        except SCons.Util.RegError:
            pass

    # if we got here, then we didn't find the registry entries:
    raise SCons.Errors.InternalError, "The %s path was not found in the registry."%path

def _get_msvc6_default_paths(version, use_mfc_dirs):
    """Return a 3-tuple of (INCLUDE, LIB, PATH) as the values of those
    three environment variables that should be set in order to execute
    the MSVC 6.0 tools properly, if the information wasn't available
    from the registry."""
    MVSdir = None
    paths = {}
    exe_path = ''
    lib_path = ''
    include_path = ''
    try:
        paths = SCons.Tool.msvs.get_msvs_install_dirs(version)
        MVSdir = paths['VSINSTALLDIR']
    except (SCons.Util.RegError, SCons.Errors.InternalError, KeyError):
        if os.environ.has_key('MSDEVDIR'):
            MVSdir = os.path.normpath(os.path.join(os.environ['MSDEVDIR'],'..','..'))
        else:
            MVSdir = r'C:\Program Files\Microsoft Visual Studio'
    if MVSdir:
        if SCons.Util.can_read_reg and paths.has_key('VCINSTALLDIR'):
            MVSVCdir = paths['VCINSTALLDIR']
        else:
            MVSVCdir = os.path.join(MVSdir,'VC98')

        MVSCommondir = r'%s\Common' % MVSdir
        if use_mfc_dirs:
            mfc_include_ = r'%s\ATL\include;%s\MFC\include;' % (MVSVCdir, MVSVCdir)
            mfc_lib_ = r'%s\MFC\lib;' % MVSVCdir
        else:
            mfc_include_ = ''
            mfc_lib_ = ''
        include_path = r'%s%s\include' % (mfc_include_, MVSVCdir)
        lib_path = r'%s%s\lib' % (mfc_lib_, MVSVCdir)

        if os.environ.has_key('OS') and os.environ['OS'] == "Windows_NT":
            osdir = 'WINNT'
        else:
            osdir = 'WIN95'

        exe_path = r'%s\tools\%s;%s\MSDev98\bin;%s\tools;%s\bin' % (MVSCommondir, osdir, MVSCommondir,  MVSCommondir, MVSVCdir)
    return (include_path, lib_path, exe_path)

def _get_msvc7_default_paths(version, use_mfc_dirs):
    """Return a 3-tuple of (INCLUDE, LIB, PATH) as the values of those
    three environment variables that should be set in order to execute
    the MSVC .NET tools properly, if the information wasn't available
    from the registry."""

    MVSdir = None
    paths = {}
    exe_path = ''
    lib_path = ''
    include_path = ''
    try:
        paths = SCons.Tool.msvs.get_msvs_install_dirs(version)
        MVSdir = paths['VSINSTALLDIR']
    except (KeyError, SCons.Util.RegError, SCons.Errors.InternalError):
        if os.environ.has_key('VSCOMNTOOLS'):
            MVSdir = os.path.normpath(os.path.join(os.environ['VSCOMNTOOLS'],'..','..'))
        else:
            # last resort -- default install location
            MVSdir = r'C:\Program Files\Microsoft Visual Studio .NET'

    if MVSdir:
        if SCons.Util.can_read_reg and paths.has_key('VCINSTALLDIR'):
            MVSVCdir = paths['VCINSTALLDIR']
        else:
            MVSVCdir = os.path.join(MVSdir,'Vc7')

        MVSCommondir = r'%s\Common7' % MVSdir
        if use_mfc_dirs:
            mfc_include_ = r'%s\atlmfc\include;' % MVSVCdir
            mfc_lib_ = r'%s\atlmfc\lib;' % MVSVCdir
        else:
            mfc_include_ = ''
            mfc_lib_ = ''
        include_path = r'%s%s\include;%s\PlatformSDK\include' % (mfc_include_, MVSVCdir, MVSVCdir)
        lib_path = r'%s%s\lib;%s\PlatformSDK\lib' % (mfc_lib_, MVSVCdir, MVSVCdir)
        exe_path = r'%s\IDE;%s\bin;%s\Tools;%s\Tools\bin' % (MVSCommondir,MVSVCdir, MVSCommondir, MVSCommondir )

        if SCons.Util.can_read_reg and paths.has_key('FRAMEWORKSDKDIR'):
            include_path = include_path + r';%s\include'%paths['FRAMEWORKSDKDIR']
            lib_path = lib_path + r';%s\lib'%paths['FRAMEWORKSDKDIR']
            exe_path = exe_path + r';%s\bin'%paths['FRAMEWORKSDKDIR']

        if SCons.Util.can_read_reg and paths.has_key('FRAMEWORKDIR') and paths.has_key('FRAMEWORKVERSION'):
            exe_path = exe_path + r';%s\%s'%(paths['FRAMEWORKDIR'],paths['FRAMEWORKVERSION'])

    return (include_path, lib_path, exe_path)

def get_msvc_paths(version=None, use_mfc_dirs=0):
    """Return a 3-tuple of (INCLUDE, LIB, PATH) as the values
    of those three environment variables that should be set
    in order to execute the MSVC tools properly."""
    exe_path = ''
    lib_path = ''
    include_path = ''

    if not version:
        versions = SCons.Tool.msvs.get_visualstudio_versions()
        if versions:
            version = versions[0] #use highest version by default
        else:
            version = '6.0'

    # Some of the configured directories only
    # appear if the user changes them from the default.
    # Therefore, we'll see if we can get the path to the MSDev
    # base installation from the registry and deduce the default
    # directories.
    if float(version) >= 7.0:
        defpaths = _get_msvc7_default_paths(version, use_mfc_dirs)
    else:
        defpaths = _get_msvc6_default_paths(version, use_mfc_dirs)

    try:
        include_path = get_msvc_path("include", version)
    except (SCons.Util.RegError, SCons.Errors.InternalError):
        include_path = defpaths[0]

    try:
        lib_path = get_msvc_path("lib", version)
    except (SCons.Util.RegError, SCons.Errors.InternalError):
        lib_path = defpaths[1]

    try:
        exe_path = get_msvc_path("path", version)
    except (SCons.Util.RegError, SCons.Errors.InternalError):
        exe_path = defpaths[2]

    return (include_path, lib_path, exe_path)

def get_msvc_default_paths(version=None, use_mfc_dirs=0):
    """Return a 3-tuple of (INCLUDE, LIB, PATH) as the values of those
    three environment variables that should be set in order to execute
    the MSVC tools properly.  This will only return the default
    locations for the tools, not the values used by MSVS in their
    directory setup area.  This can help avoid problems with different
    developers having different settings, and should allow the tools
    to run in most cases."""

    if not version and not SCons.Util.can_read_reg:
        version = '6.0'

    try:
        if not version:
            version = SCons.Tool.msvs.get_visualstudio_versions()[0] #use highest version
    except KeyboardInterrupt:
        raise
    except:
        pass

    if float(version) >= 7.0:
        return _get_msvc7_default_paths(version, use_mfc_dirs)
    else:
        return _get_msvc6_default_paths(version, use_mfc_dirs)

#############################################################
# amz backported the code from the current scons cvs version for
# the visual studio 2005 stuff.

def get_visualstudio8_suites():
    """
    Returns a sorted list of all installed Visual Studio 2005 suites found
    in the registry. The highest version should be the first entry in the list.
    """

    suites = []

    # Detect Standard, Professional and Team edition
    try:
        idk = SCons.Util.RegOpenKeyEx(SCons.Util.HKEY_LOCAL_MACHINE,
            r'Software\Microsoft\VisualStudio\8.0')
        id = SCons.Util.RegQueryValueEx(idk, 'InstallDir')
        editions = { 'PRO': r'Setup\VS\Pro' }       # ToDo: add standard and team editions
        edition_name = 'STD'
        for name, key_suffix in editions.items():
            try:
                idk = SCons.Util.RegOpenKeyEx(SCons.Util.HKEY_LOCAL_MACHINE,
                    r'Software\Microsoft\VisualStudio\8.0' + '\\' + key_suffix )
                edition_name = name
            except SCons.Util.RegError:
                pass
            suites.append(edition_name)
    except SCons.Util.RegError:
        pass

    # Detect Express edition
    try:
        idk = SCons.Util.RegOpenKeyEx(SCons.Util.HKEY_LOCAL_MACHINE,
            r'Software\Microsoft\VCExpress\8.0')
        id = SCons.Util.RegQueryValueEx(idk, 'InstallDir')
        suites.append('EXPRESS')
    except SCons.Util.RegError:
        pass

    return suites

version_re = re.compile(r'(\d+\.\d+)(.*)')

def msvs_parse_version(s):
    """
    Split a Visual Studio version, which may in fact be something like
    '7.0Exp', into is version number (returned as a float) and trailing
    "suite" portion.
    """
    num, suite = version_re.match(s).groups()
    return float(num), suite

def get_msvs8_install_dirs(version = None, vs8suite = None):
    """
    Get installed locations for various msvc-related products, like the .NET SDK
    and the Platform SDK.
    """

    if not SCons.Util.can_read_reg:
        return {}

    if not version:
        versions = get_visualstudio_versions()
        if versions:
            version = versions[0] #use highest version by default
        else:
            return {}

    rv = {}

    version_num, suite = msvs_parse_version(version)

    K = 'Software\\Microsoft\\VisualStudio\\' + str(version_num)
    if (version_num >= 8.0):
        if vs8suite == None:
            # We've been given no guidance about which Visual Studio 8
            # suite to use, so attempt to autodetect.
            suites = get_visualstudio8_suites()
            if suites:
                vs8suite = suites[0]
                rv['VS8SUITE'] = vs8suite

        if vs8suite == 'EXPRESS':
            K = 'Software\\Microsoft\\VCExpress\\' + str(version_num)

    # vc++ install dir
    if (version_num < 7.0):
        key = K + r'\Setup\Microsoft Visual C++\ProductDir'
    else:
        key = K + r'\Setup\VC\ProductDir'
    try:
        (rv['VCINSTALLDIR'], t) = SCons.Util.RegGetValue(SCons.Util.HKEY_LOCAL_MACHINE, key)
    except SCons.Util.RegError:
        pass

    # visual studio install dir
    if (version_num < 7.0):
        try:
            (rv['VSINSTALLDIR'], t) = SCons.Util.RegGetValue(SCons.Util.HKEY_LOCAL_MACHINE,
                                                             K + r'\Setup\Microsoft Visual Studio\ProductDir')
        except SCons.Util.RegError:
            pass

        if not rv.has_key('VSINSTALLDIR') or not rv['VSINSTALLDIR']:
            if rv.has_key('VCINSTALLDIR') and rv['VCINSTALLDIR']:
                rv['VSINSTALLDIR'] = os.path.dirname(rv['VCINSTALLDIR'])
            else:
                rv['VSINSTALLDIR'] = os.path.join(SCons.Platform.win32.get_program_files_dir(),'Microsoft Visual Studio')
    else:
        try:
            (rv['VSINSTALLDIR'], t) = SCons.Util.RegGetValue(SCons.Util.HKEY_LOCAL_MACHINE,
                                                             K + r'\Setup\VS\ProductDir')
        except SCons.Util.RegError:
            pass

    # .NET framework install dir
    try:
        (rv['FRAMEWORKDIR'], t) = SCons.Util.RegGetValue(SCons.Util.HKEY_LOCAL_MACHINE,
            r'Software\Microsoft\.NETFramework\InstallRoot')
    except SCons.Util.RegError:
        pass

    if rv.has_key('FRAMEWORKDIR'):
        # try and enumerate the installed versions of the .NET framework.
        contents = os.listdir(rv['FRAMEWORKDIR'])
        l = re.compile('v[0-9]+.*')
        versions = []
        for entry in contents:
            if l.match(entry):
                versions.append(entry)

        def versrt(a,b):
            # since version numbers aren't really floats...
            aa = a[1:]
            bb = b[1:]
            aal = aa.split('.')
            bbl = bb.split('.')
            c = int(bbl[0]) - int(aal[0])
            if c == 0:
                c = int(bbl[1]) - int(aal[1])
                if c == 0:
                    c = int(bbl[2]) - int(aal[2])
            return c

        versions.sort(versrt)

        rv['FRAMEWORKVERSIONS'] = versions
        # assume that the highest version is the latest version installed
        rv['FRAMEWORKVERSION'] = versions[0]

    # .NET framework SDK install dir
    try:
        if rv.has_key('FRAMEWORKVERSION') and rv['FRAMEWORKVERSION'][:4] == 'v1.1':
            key = r'Software\Microsoft\.NETFramework\sdkInstallRootv1.1'
        else:
            key = r'Software\Microsoft\.NETFramework\sdkInstallRoot'

        (rv['FRAMEWORKSDKDIR'], t) = SCons.Util.RegGetValue(SCons.Util.HKEY_LOCAL_MACHINE,key)

    except SCons.Util.RegError:
        pass

    # MS Platform SDK dir
    try:
        (rv['PLATFORMSDKDIR'], t) = SCons.Util.RegGetValue(SCons.Util.HKEY_LOCAL_MACHINE,
            r'Software\Microsoft\MicrosoftSDK\Directories\Install Dir')
    except SCons.Util.RegError:
        pass

    # check for existence
    if rv.has_key('PLATFORMSDKDIR'):
        if not os.path.exists(rv['PLATFORMSDKDIR']):
            del rv['PLATFORMSDKDIR']

    # ok now look for something like this:
    # Software\Microsoft\MicrosoftSDK\InstalledSDKs\HKEY_CURRENT_USER\Software\Microsoft\MicrosoftSDK\InstalledSDKs\8F9E5EF3-A9A5-491B-A889-C58EFFECE8B3\Install Dir
    if not rv.has_key('PLATFORMSDKDIR'):
        try:
            loc = r'Software\Microsoft\MicrosoftSDK\InstalledSDKs'
            k = SCons.Util.RegOpenKeyEx(SCons.Util.HKEY_LOCAL_MACHINE,loc)
            i = 0
            while 1:
                try:
                    key = SCons.Util.RegEnumKey(k,i)
                    try:
                        (rv['PLATFORMSDKDIR'], t) = SCons.Util.RegGetValue(SCons.Util.HKEY_LOCAL_MACHINE, r'Software\Microsoft\MicrosoftSDK\InstalledSDKs\\' + key + r'\Install Dir')
                    except SCons.Util.RegError:
                        pass
                    i = i + 1
                except SCons.Util.RegError:
                    break;
        except SCons.Util.RegError:
            pass

    if rv.has_key('PLATFORMSDKDIR'):
        # if we have a platform SDK, try and get some info on it.
        vers = {}
        try:
            loc = r'Software\Microsoft\MicrosoftSDK\InstalledSDKs'
            k = SCons.Util.RegOpenKeyEx(SCons.Util.HKEY_LOCAL_MACHINE,loc)
            i = 0
            while 1:
                try:
                    key = SCons.Util.RegEnumKey(k,i)
                    sdk = SCons.Util.RegOpenKeyEx(k,key)
                    j = 0
                    name = ''
                    date = ''
                    version = ''
                    while 1:
                        try:
                            (vk,vv,t) = SCons.Util.RegEnumValue(sdk,j)
                            if vk.lower() == 'keyword':
                                name = vv
                            if vk.lower() == 'propagation_date':
                                date = vv
                            if vk.lower() == 'version':
                                version = vv
                            j = j + 1
                        except SCons.Util.RegError:
                            break
                    if name:
                        vers[name] = (date, version)
                    i = i + 1
                except SCons.Util.RegError:
                    break
            rv['PLATFORMSDK_MODULES'] = vers
        except SCons.Util.RegError:
            pass
    return rv


def _get_msvc8_default_paths(version = None, vs8suite = None):

    rv = get_msvs8_install_dirs(version, vs8suite)
    include_path = ""
    include_path += os.path.join(rv['VCINSTALLDIR'], 'include') + ';'
    # In the express edition there is no PlatformSDK.
    if rv['VS8SUITE'] == 'EXPRESS':
        if rv.has_key('PLATFORMSDKDIR'):
            include_path += os.path.join(rv['PLATFORMSDKDIR'], 'include') + ';'
            include_path += os.path.join(rv['PLATFORMSDKDIR'], 'include', 'atl')
        else:
            print "Couldn't find platform sdk install directory!"
    else:
        include_path += os.path.join(rv['VCINSTALLDIR'], 'PlatformSDK', 'include') + ';'
        include_path += os.path.join(rv['VCINSTALLDIR'], 'PlatformSDK', 'include', 'atl')

    lib_path = ""
    lib_path += os.path.join(rv['VCINSTALLDIR'], 'lib') + ';'
    lib_path += os.path.join(rv['VSINSTALLDIR'], 'SDK', 'v2.0', 'lib') + ';'
    if rv['VS8SUITE'] == 'EXPRESS':
        if rv.has_key('PLATFORMSDKDIR'):
            lib_path += os.path.join(rv['PLATFORMSDKDIR'], 'lib')
        else:
            print "Couldn't find platform sdk install directory!"
    else:
        lib_path += os.path.join(rv['VCINSTALLDIR'], 'PlatformSDK', 'lib')

    exe_path = ""
    exe_path += os.path.join(rv['VSINSTALLDIR'], 'Common7', 'IDE') + ';'
    exe_path += os.path.join(rv['VCINSTALLDIR'], 'bin') + ';'
    exe_path += os.path.join(rv['VSINSTALLDIR'], 'Common7', 'Tools') + ';'
    exe_path += os.path.join(rv['VSINSTALLDIR'], 'SDK', 'v2.0', 'bin') + ';'
    exe_path += os.path.join(rv['FRAMEWORKDIR'], rv['FRAMEWORKVERSION']) + ';'
    exe_path += os.path.join(rv['VCINSTALLDIR'], 'VCPackages')

    return (include_path, lib_path, exe_path)

def _get_msvc8_x64_default_paths(version = None, vs8suite = None):

    rv = get_msvs8_install_dirs(version, vs8suite)
    include_path = ""
    include_path += os.path.join(rv['VCINSTALLDIR'], 'atlmfc', 'include') + ';'
    include_path += os.path.join(rv['VCINSTALLDIR'], 'include') + ';'
    include_path += os.path.join(rv['VCINSTALLDIR'], 'PlatformSDK', 'include') + ';'
    include_path += os.path.join(rv['VSINSTALLDIR'], 'SDK', 'v2.0', 'include')

    lib_path = ""
    lib_path += os.path.join(rv['VCINSTALLDIR'], 'atlmfc', 'lib', 'amd64') + ';'
    lib_path += os.path.join(rv['VCINSTALLDIR'], 'lib', 'amd64') + ';'
    lib_path += os.path.join(rv['VCINSTALLDIR'], 'PlatformSDK', 'lib', 'amd64') + ';'
    lib_path += os.path.join(rv['VSINSTALLDIR'], 'SDK', 'v2.0', 'lib', 'amd64')

    exe_path = ""
    exe_path += os.path.join(rv['VCINSTALLDIR'], 'bin', 'amd64') + ';'
    exe_path += os.path.join(rv['VCINSTALLDIR'], 'PlatformSDK', 'bin', 'win64', 'amd64') + ';'
    exe_path += os.path.join(rv['VCINSTALLDIR'], 'PlatformSDK', 'bin') + ';'
    exe_path += os.path.join(rv['VCINSTALLDIR'], 'VCPackages')
    exe_path += os.path.join(rv['VSINSTALLDIR'], 'Common7', 'IDE') + ';'
    exe_path += os.path.join(rv['VSINSTALLDIR'], 'Common7', 'Tools') + ';'
    exe_path += os.path.join(rv['VSINSTALLDIR'], 'Common7', 'Tools', 'bin') + ';'
    exe_path += os.path.join(rv['VSINSTALLDIR'], 'SDK', 'v2.0', 'bin')

    return (include_path, lib_path, exe_path)

def _get_mspsdk_x64_default_paths(version = None, vs8suite = None):

    rv = get_msvs8_install_dirs(version, vs8suite)

    include_path = ""
    if rv.has_key('PLATFORMSDKDIR'):
        include_path += os.path.join(rv['PLATFORMSDKDIR'], 'include') + ';'
        include_path += os.path.join(rv['PLATFORMSDKDIR'], 'include', 'crt') + ';'
        include_path += os.path.join(rv['PLATFORMSDKDIR'], 'include', 'crt', 'sys') + ';'
        include_path += os.path.join(rv['PLATFORMSDKDIR'], 'include', 'mfc') + ';'
        include_path += os.path.join(rv['PLATFORMSDKDIR'], 'include', 'atl')
    else:
        print "Couldn't find platform sdk install directory!"

    lib_path = ""
    if rv.has_key('PLATFORMSDKDIR'):
        lib_path += os.path.join(rv['PLATFORMSDKDIR'], 'lib', 'amd64') + ';'
        lib_path += os.path.join(rv['PLATFORMSDKDIR'], 'lib', 'amd64', 'atlmfc')
    else:
        print "Couldn't find platform sdk install directory!"

    exe_path = ""
    if rv.has_key('PLATFORMSDKDIR'):
        exe_path += os.path.join(rv['PLATFORMSDKDIR'], 'Bin', 'Win64', 'x86', 'AMD64') + ';'
        exe_path += os.path.join(rv['PLATFORMSDKDIR'], 'bin') + ';'
        exe_path += os.path.join(rv['PLATFORMSDKDIR'], 'bin', 'WinNT') + ';'
        exe_path += 'C:/WINDOWS/system32;C:/WINDOWS;C:/WINDOWS/System32/Wbem'
    else:
        print "Couldn't find platform sdk install directory!"

    return (include_path, lib_path, exe_path)

####################################################

def validate_vars(env):
    """Validate the PCH and PCHSTOP construction variables."""
    if env.has_key('PCH') and env['PCH']:
        if not env.has_key('PCHSTOP'):
            raise SCons.Errors.UserError, "The PCHSTOP construction must be defined if PCH is defined."
        if not SCons.Util.is_String(env['PCHSTOP']):
            raise SCons.Errors.UserError, "The PCHSTOP construction variable must be a string: %r"%env['PCHSTOP']

def pch_emitter(target, source, env):
    """Adds the object file target."""

    validate_vars(env)

    pch = None
    obj = None

    for t in target:
        if SCons.Util.splitext(str(t))[1] == '.pch':
            pch = t
        if SCons.Util.splitext(str(t))[1] == '.obj':
            obj = t

    if not obj:
        obj = SCons.Util.splitext(str(pch))[0]+'.obj'

    target = [pch, obj] # pch must be first, and obj second for the PCHCOM to work

    return (target, source)

def object_emitter(target, source, env, parent_emitter):
    """Sets up the PCH dependencies for an object file."""

    validate_vars(env)

    parent_emitter(target, source, env)

    if env.has_key('PCH') and env['PCH']:
        env.Depends(target, env['PCH'])

    return (target, source)

def static_object_emitter(target, source, env):
    return object_emitter(target, source, env,
                          SCons.Defaults.StaticObjectEmitter)

def shared_object_emitter(target, source, env):
    return object_emitter(target, source, env,
                          SCons.Defaults.SharedObjectEmitter)

pch_builder = SCons.Builder.Builder(action='$PCHCOM', suffix='.pch', emitter=pch_emitter,
                                    source_scanner=SCons.Defaults.ObjSourceScan)
res_builder = SCons.Builder.Builder(action='$RCCOM', suffix='.res',
                                    source_scanner=SCons.Defaults.ObjSourceScan)
SCons.Defaults.ObjSourceScan.add_scanner('.rc', SCons.Defaults.CScan)

def generate(env):
    """Add Builders and construction variables for MSVC++ to an Environment."""
    static_obj, shared_obj = SCons.Tool.createObjBuilders(env)

    for suffix in CSuffixes:
        static_obj.add_action(suffix, SCons.Defaults.CAction)
        shared_obj.add_action(suffix, SCons.Defaults.ShCAction)
        static_obj.add_emitter(suffix, static_object_emitter)
        shared_obj.add_emitter(suffix, shared_object_emitter)

    for suffix in CXXSuffixes:
        static_obj.add_action(suffix, SCons.Defaults.CXXAction)
        shared_obj.add_action(suffix, SCons.Defaults.ShCXXAction)
        static_obj.add_emitter(suffix, static_object_emitter)
        shared_obj.add_emitter(suffix, shared_object_emitter)

    env['CCPDBFLAGS'] = SCons.Util.CLVar(['${(PDB and "/Z7") or ""}'])
    env['CCPCHFLAGS'] = SCons.Util.CLVar(['${(PCH and "/Yu%s /Fp%s"%(PCHSTOP or "",File(PCH))) or ""}'])
    env['CCCOMFLAGS'] = '$CPPFLAGS $_CPPDEFFLAGS $_CPPINCFLAGS /c $SOURCES /Fo$TARGET $CCPCHFLAGS $CCPDBFLAGS'
    env['CC']         = 'cl'
    env['CCFLAGS']    = SCons.Util.CLVar('/nologo')
    env['CCCOM']      = '$CC $CCFLAGS $CCCOMFLAGS'
    env['SHCC']       = '$CC'
    env['SHCCFLAGS']  = SCons.Util.CLVar('$CCFLAGS')
    env['SHCCCOM']    = '$SHCC $SHCCFLAGS $CCCOMFLAGS'
    env['CXX']        = '$CC'
    env['CXXFLAGS']   = SCons.Util.CLVar('$CCFLAGS $( /TP $)')
    env['CXXCOM']     = '$CXX $CXXFLAGS $CCCOMFLAGS'
    env['SHCXX']      = '$CXX'
    env['SHCXXFLAGS'] = SCons.Util.CLVar('$CXXFLAGS')
    env['SHCXXCOM']   = '$SHCXX $SHCXXFLAGS $CCCOMFLAGS'
    env['CPPDEFPREFIX']  = '/D'
    env['CPPDEFSUFFIX']  = ''
    env['INCPREFIX']  = '/I'
    env['INCSUFFIX']  = ''
#    env.Append(OBJEMITTER = [static_object_emitter])
#    env.Append(SHOBJEMITTER = [shared_object_emitter])
    env['STATIC_AND_SHARED_OBJECTS_ARE_THE_SAME'] = 1

    env['RC'] = 'rc'
    env['RCFLAGS'] = SCons.Util.CLVar('')
    env['RCCOM'] = '$RC $_CPPDEFFLAGS $_CPPINCFLAGS $RCFLAGS /fo$TARGET $SOURCES'
    env['BUILDERS']['RES'] = res_builder
    env['OBJPREFIX']      = ''
    env['OBJSUFFIX']      = '.obj'
    env['SHOBJPREFIX']    = '$OBJPREFIX'
    env['SHOBJSUFFIX']    = '$OBJSUFFIX'

    try:
        version = SCons.Tool.msvs.get_default_visualstudio_version(env)

        # By default, add the MFC directories, because this is what
        # we've been doing for a long time.  We may change this.
        use_mfc_dirs = env.get('MSVS_USE_MFC_DIRS', 1)
        if env.get('MSVS_IGNORE_IDE_PATHS', 0):
            _get_paths = get_msvc_default_paths
        else:
            _get_paths = get_msvc_paths
        include_path, lib_path, exe_path = _get_paths(version, use_mfc_dirs)

        # since other tools can set these, we just make sure that the
        # relevant stuff from MSVS is in there somewhere.
        env.PrependENVPath('INCLUDE', include_path)
        env.PrependENVPath('LIB', lib_path)
        env.PrependENVPath('PATH', exe_path)
    except (SCons.Util.RegError, SCons.Errors.InternalError):
        pass

    env['CFILESUFFIX'] = '.c'
    env['CXXFILESUFFIX'] = '.cc'

    env['PCHPDBFLAGS'] = SCons.Util.CLVar(['${(PDB and "/Yd") or ""}'])
    env['PCHCOM'] = '$CXX $CXXFLAGS $CPPFLAGS $_CPPDEFFLAGS $_CPPINCFLAGS /c $SOURCES /Fo${TARGETS[1]} /Yc$PCHSTOP /Fp${TARGETS[0]} $CCPDBFLAGS $PCHPDBFLAGS'
    env['BUILDERS']['PCH'] = pch_builder

def exists(env):
    if SCons.Tool.msvs.is_msvs_installed():
        # there's at least one version of MSVS installed.
        return 1
    else:
        return env.Detect('cl')

