import fnmatch
import os.path
import string
import sys
import shutil
import zipfile
import glob

SConsignFile()
#CacheDir('cache')

def Glob(match):
    """Similar to glob.glob, except globs SCons nodes, and thus sees
    generated files and files from build directories.  Basically, it sees
    anything SCons knows about."""
    def fn_filter(node):
        fn = str(node)
        return fnmatch.fnmatch(os.path.basename(fn), match)

    here = Dir('.')

    children = here.all_children()
    nodes = map(File, filter(fn_filter, children))
    node_srcs = [n.srcnode() for n in nodes]

    src = here.srcnode()
    if src is not here:
        src_children = map(File, filter(fn_filter, src.all_children()))
        for s in src_children:
            if s not in node_srcs:
                nodes.append(File(os.path.basename(str(s))))

    return nodes

Export('Glob')

PLATFORM = DefaultEnvironment().get('PLATFORM')

if PLATFORM == 'win32':

    def GetCygwinPath(path):
        f = os.popen('cygpath -w -p ' + path, 'r')
        for wpath in f.xreadlines():
            # remove line feed
            if wpath[-1:] == '\n':
                wpath = wpath[:len(wpath)-1]
        return wpath

    Export('GetCygwinPath')

elif PLATFORM == 'cygwin':
    
    def GetCygwinPath(path):
        return path
    
    Export('GetCygwinPath')

class unzip:
    def __init__(self, verbose = False, percent = 10):
        self.verbose = verbose
        self.percent = percent
        
    def extract(self, file, dir):
        if not dir.endswith(':') and not os.path.exists(dir):
            os.mkdir(dir)

        zf = zipfile.ZipFile(file)

        # create directory structure to house files
        self._createstructure(file, dir)

        num_files = len(zf.namelist())
        percent = self.percent
        divisions = 100 / percent
        perc = int(num_files / divisions)

        # extract files to directory structure
        for i, name in enumerate(zf.namelist()):

            if self.verbose == True:
                print "Extracting %s" % name
            elif (i % perc) == 0 and i > 0:
                complete = int (i / perc) * percent
                print "%s%% complete" % complete

            if not name.endswith('/'):
                outfile = open(os.path.join(dir, name), 'wb')
                outfile.write(zf.read(name))
                outfile.flush()
                outfile.close()


    def _createstructure(self, file, dir):
        self._makedirs(self._listdirs(file), dir)


    def _makedirs(self, directories, basedir):
        """ Create any directories that don't currently exist """
        for dir in directories:
            curdir = os.path.join(basedir, dir)
            if not os.path.exists(curdir):
                os.mkdir(curdir)

    def _listdirs(self, file):
        """ Grabs all the directories in the zip structure
        This is necessary to create the structure before trying
        to extract the file to it. """
        zf = zipfile.ZipFile(file)

        dirs = []

        for name in zf.namelist():
            if name.endswith('/'):
                dirs.append(name)

        dirs.sort()
        return dirs



def get_timestamp(file):
    if os.path.exists(file):
        return os.path.getmtime(file)
    else:
        return 0


def MyInstall(dst, src):
    if get_timestamp(src) == get_timestamp(dst):
        return 0

    try:
        os.unlink(dst)
    except OSError:
        pass

    try:
        import stat
        # Create directories if not existent.
        if not os.path.isdir(os.path.dirname(dst)):
            os.makedirs(os.path.dirname(dst))
        shutil.copy2(src, dst)

        st=os.stat(src)
        os.chmod(dst, stat.S_IMODE(st[stat.ST_MODE]) | stat.S_IWRITE)
        print 'INSTALLED "%s"' % (dst)
        return 0
    except (IOError, os.error), why:
        print "Couldn't install %s: %s" % (`dst`, str(why))
        return -1

def AppendFilesUnique(files, adds):
    for add in adds:
        found = 0
        for file in files:
            filename = str(file)
            if filename.find(add) > 0:
                found = 1
                break;
        if found == 0:
            files.append(add)

Export('AppendFilesUnique')

# qt stuff

def GetMocSources(sources):
    # create ui source
    new_sources = []
    for source in sources:
        srcname = os.path.basename(str(source))
        new_sources.append(srcname[:-2] + "_moc.cpp")
    return new_sources

Export('GetMocSources')

def CreateMocSources(env, sources):
    # create moc source
    for source in sources:
        srcname = os.path.basename(str(source))
        if srcname[-2:] == '.h':
            # we should scan for Q_OBJECT ...
            target = srcname[:-2] + "_moc.cpp"
            env.Command(target, source, ["moc $SOURCES -o $TARGET"])

Export('CreateMocSources')

def GetUiSources(sources):
    # create ui source
    new_sources = []
    new_headers = []
    for source in sources:
        srcname = os.path.basename(str(source))
        name = srcname[:-3]
        new_sources.append("uic_" + name + ".cpp")
        new_headers.append("uic_" + name + ".h")
    return new_sources, new_headers

Export('GetUiSources')

def CreateUiSources(env, sources):
        # create ui source
        cpp_sources = []
        ui_moc_h_sources = []
        for source in sources:
            srcname = os.path.basename(str(source))
            name = srcname[:-3]
            target1 = "uic_" + name + ".h"
            env.Command(target1, source, ["uic -o $TARGET $SOURCES"])
            target2 = "uic_" + name + ".cpp"
            env.Command(target2, source, ["uic -o $TARGET -impl " + target1 + " $SOURCES"])
            cpp_sources.append(target2)
            ui_moc_h_sources.append(target1)
        return cpp_sources, ui_moc_h_sources

Export('CreateUiSources')

def CreateWinHeaders(env):

    if sys.platform != 'win32':
        return

    build_dir = str(env['BUILD_DIR'])
    path = os.path.join(build_dir, 'Source', 'Base')

    # create directories
    if not os.path.isdir(path):
        os.makedirs(path)

    filename = os.path.join(path, 'unistd.h')
    if not os.path.exists(filename):
        unistd_h = open(filename, 'w')
        unistd_h.close()
        MyInstall(os.path.join(build_dir, 'installed', 'include', 'OpenSG', 'unistd.h'), filename)
    
    if tc.get_name() == 'win32-icl':
        filename = os.path.join(path, 'xtree')
        if not os.path.exists(filename):
            shutil.copy2(os.path.join(build_dir, '..', '..', 'VSBuild', 'VS6', 'xtree'), filename)
            MyInstall(os.path.join(build_dir, 'installed', 'include', 'OpenSG', 'xtree'), filename)

def CreateConfiguredHeader(env):

    build_dir = str(env['BUILD_DIR'])
    path = os.path.join(build_dir, 'Source', 'Base')

    is_win32 = 0
    is_linux = 0

    if sys.platform == 'win32':
        is_win32 = 1
    elif sys.platform == 'linux2':
        is_linux = 1

    filename = os.path.join(path, 'OSGConfigured.h')
    
    if not os.path.exists(filename):

        # Create directories if not existent.
        if not os.path.isdir(path):
            os.makedirs(path)
    
        configured_h = open(filename, 'w')
        
        configured_h.write("""
/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
 *                                                                           *
 *   contact: reiners@igd.fhg.de, gerrit.voss@vossg.org, jbehr@zgdv.de       *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//
// This file was automatically generated by configuration script.
//

#ifndef _OSGCONFIGURED_H_
#define _OSGCONFIGURED_H_

#if defined (OSG_USE_WINTHREADS)
#define OSG_ASPECT_USE_LOCALSTORAGE 1
#endif

#if defined(OSG_WIN_TYPES)
/* #undef OSG_BOOL_IS_UNSIGNED */
#endif

#define OSG_DEFAULT_LOG_LEVEL LOG_WARNING
#define OSG_DEFAULT_LOG_TYPE LOG_STDERR

#ifndef OSG_DEFAULT_LOG_LEVEL
#    define OSG_DEFAULT_LOG_LEVEL LOG_WARNING
#endif

#ifndef OSG_DEFAULT_LOG_TYPE
#    define OSG_DEFAULT_LOG_TYPE LOG_STDERR 
#endif

/* #undef OSG_DISABLE_DEPRECATED */

#if defined(OSG_DEBUG)
/* #undef OSG_DEBUG_FCPTR */
/* #undef OSG_DEBUG_NO_FCPTR_ARITHM */
#endif

#define OSG_OPT_DRAWTREE 1

/* #undef OSG_PTHREAD_ELF_TLS */

/* #undef OSG_NO_GLUT_GLSUBDIR */

#if defined(WIN32) && ! defined(__ICL)
#pragma warning( disable : 4786 4661 4305 )
#endif

/* #undef OSG_SGI_USE_PTHREAD */
#define OSG_SGI_USE_SPROC 1

#if defined(__sgi)
#   if defined(OSG_SGI_USE_PTHREAD)
#       define OSG_USE_PTHREADS
#       define OSG_ASPECT_USE_PTHREADKEY
/* #       undef  OSG_USE_SPROC */
#   else
#       define OSG_USE_SPROC
#   endif
#endif

/* #undef OSG_USE_MPATROL */

#if defined(OSG_USE_MPATROL)
#define MP_NONEWDELETE 1
#include <mpatrol.h>
#endif

/* #undef OSG_ICC_GNU_COMPAT */

#endif
        """)

        #if is_win32:
        #    configured_h.write('\n')

        configured_h.write('\n') # add new line
        configured_h.close()

    MyInstall(os.path.join(build_dir, 'installed', 'include', 'OpenSG', 'OSGConfigured.h'), filename)

def InstallProgram(env, prog):
    if env.get('OSG_PROGDIR'):
        env.Install('$PREFIX/lib/$OSG_PROGDIR', prog)
    else:
        env.Install('$PREFIX/lib', prog)

def BuildProgram(tc, name, sources, tools=[], updates=[], **kw):
    from os.path import basename, join
    from SCons.Util import splitext

    for env in tc.get_env_list():
        env = env.Copy()
        for t in tools:   env.Tool(t)
        for u in updates: u(env)
        apply(env.Append, [], kw)

        def base(n): return splitext(basename(str(n)))[0]
        objects = [env.Object("${OSG_OBJDIR}/" + base(k), k) for k in sources]

        target = name + '${OSG_PROGSUF}'
        if env.get('OSG_PROGDIR'):
            target = join('$OSG_PROGDIR', target)

        prog = env.Program(target, objects)
        InstallProgram(env, prog)


class OpenSGLibrary:
    def __init__(self, libraries):
        if type(libraries) != type([]):
            libraries = [libraries]
        self.libraries = libraries

    def __call__(self, env):
        if env.get('OSG_LIBDIR'):
            libdir = env['PREFIX'].Dir('lib').Dir(env['OSG_LIBDIR'])
        else:
            libdir = env['PREFIX'].Dir('lib')

        env.AppendUnique(LIBPATH = [Dir(libdir)])
        
        for lib in self.libraries:
            env.AppendUnique(LIBS = [lib + '$OSG_LIBSUF'])


Export('BuildProgram OpenSGLibrary')



def CreateEnvironment(*args, **kw):
    "Creates an environment with some things that always have to be set."
    env = apply(Environment, args, kw)
    env['ENV']['HOME'] = os.environ.get('HOME')
    return env


win32_defines = ['WIN32', '_WINDOWS', 'WINVER=0x0400', '_WIN32_WINDOWS=0x0410',
                 '_WIN32_WINNT=0x0400',
                 'STRICT', 'NOMINMAX']

# with this define I get identifier "htonl" is undefined.
#win32_defines += ['WIN32_LEAN_AND_MEAN']

# OSGConfigured.h stuff

win32_defines += ['_OSG_HAVE_CONFIGURED_H_']

#win32_defines += ['OSG_ASPECT_USE_LOCALSTORAGE=1', 'OSG_DEFAULT_LOG_TYPE=2',
#                  'OSG_DEFAULT_LOG_LEVEL=2']

# ok we need to add some kind of configure for creating the OSGConfigured.h header file.
# '_OSG_HAVE_CONFIGURED_H_'

class PlatformOptions:
    def __init__(self, opts):
        self.de = DefaultEnvironment()

        # check the QTDIR variable and set 'yes'
        opts.Add(PackageOption('qt', 'Enable qt support', 'no'))

        opts.Add(PackageOption('cg', 'Enable cg support', 'no'))

        opts.Add(BoolOption('gif', 'Enable gif support', 1))

        self.package_options = ['tif', 'jpg', 'png', 'glut', 'zlib']
        
        if self.de.get('PLATFORM') == 'cygwin':
            print "Not supported yet!"
        elif self.de.get('PLATFORM') == 'win32':
            opts.Add(EnumOption('compiler', 'Use compiler', 'icl',
                                    allowed_values=('gcc', 'icl', 'msvc70', 'msvc71', 'msvc80')))
            
            # try to find the supportslibs directory.
            current_dir = Dir('.').abspath
            supportlibs = 'no'
            if os.path.exists(os.path.join(current_dir , '..', 'supportlibs', 'include', 'png.h')):
                supportlibs = 'yes'
            else:
                # unzip supportlibs
                print 'unzipping win32 supportlibs ...'
                un = unzip()
                un.extract(os.path.join(current_dir , 'dist', 'win', 'supportlibs.zip'),
                           os.path.join(current_dir , '..', 'supportlibs'))
                if os.path.exists(os.path.join(current_dir , '..', 'supportlibs', 'include', 'png.h')):
                    supportlibs = 'yes'

            for option in self.package_options:
                opts.Add(PackageOption(option, 'Enable ' + option + ' support', supportlibs))
        else:
            if sys.platform == 'linux2':
                opts.Add(EnumOption('compiler', 'Use compiler', 'gcc',
                                    allowed_values=('gcc')))
                
                for option in self.package_options:
                    opts.Add(PackageOption(option, 'Enable ' + option + ' support', 'yes'))

        # add common options
        opts.Add(EnumOption('type', 'Compile dbg, opt or both', 'opt',
                            allowed_values=('dbg', 'opt', 'both', 'dbgopt')))

        opts.Add(BoolOption('gv_beta', 'enable gv beta', 0))

        opts.Add(BoolOption('invalid_pointer_check', 'enable invalid pointer check', 0))

        # contrib
        opts.Add(BoolOption('contrib_cgchunk', 'enable contrib CGChunk', 0))
        opts.Add(BoolOption('contrib_cgfxmaterial', 'enable contrib CGFXMaterial', 0))
        opts.Add(BoolOption('contrib_drawfunctorcore', 'enable contrib DrawFunctorCore', 0))
        opts.Add(BoolOption('contrib_ply', 'enable ply loader', 0))
        opts.Add(BoolOption('contrib_terrain', 'enable terrain rendering node', 0))

        opts.Update(self.de)

    def getOption(self, opt):
        return self.de.get(opt)

    def getPackageOptions(self):
        return self.package_options

    def buildDbgOpt(self):
        return (self.getOption('type') == 'dbgopt')

    def buildDbg(self):
        return (self.getOption('type') == 'dbg' or self.getOption('type') == 'both')
    
    def buildOpt(self):
        return (self.getOption('type') == 'opt' or self.getOption('type') == 'both')

    def getPlatform(self):
        return self.de.get('PLATFORM')

def moveGVBetaFile(base, file):
    src = os.path.join(base, file)
    dst = os.path.join(base, 'tmp_gv')
    if not os.path.exists(dst):
        os.makedirs(dst)
    dst = os.path.join(base, 'tmp_gv', file)
    if os.path.exists(src) and not os.path.exists(dst):
        shutil.move(src, dst)
    if os.path.exists(src):
        os.unlink(src)

def unmoveGVBetaFile(base, file):
    src = os.path.join(base, 'tmp_gv', file)
    dst = os.path.join(base, file)
    if os.path.exists(src):
        if os.path.exists(dst):
            os.unlink(dst)
        shutil.move(src, base)

    dst = os.path.join(base, 'tmp_gv')
    if os.path.exists(dst):
        # if the directory is not empty ignore the exception.
        try:
            os.rmdir(dst)
        except:
            dummy = 1

def moveGVBetaFiles():
    current_dir = Dir('.').abspath

    moveGVBetaFile(os.path.join(current_dir, 'Source', 'Base', 'Base'),
                   'OSGTypeBase.h')

    moveGVBetaFile(os.path.join(current_dir, 'Source', 'Base', 'Base'),
                   'OSGTypeBase.cpp')

    moveGVBetaFile(os.path.join(current_dir, 'Source', 'Base', 'Base'),
                   'OSGTypeFactory.h')

    moveGVBetaFile(os.path.join(current_dir, 'Source', 'Base', 'Base'),
                   'OSGTypeFactory.cpp')

    moveGVBetaFile(os.path.join(current_dir, 'Source', 'System', 'FileIO', 'OBJ'),
                   'OSGOBJSceneFileType.cpp')

    moveGVBetaFile(os.path.join(current_dir, 'Source', 'System', 'FileIO', 'WRL'),
                   'OSGVRMLSceneFileType.h')

    moveGVBetaFile(os.path.join(current_dir, 'Source', 'System', 'FileIO', 'WRL'),
                   'OSGVRMLSceneFileType.cpp')


def unmoveGVBetaFiles():
    current_dir = Dir('.').abspath

    unmoveGVBetaFile(os.path.join(current_dir, 'Source', 'Base', 'Base'),
                     'OSGTypeBase.h')

    unmoveGVBetaFile(os.path.join(current_dir, 'Source', 'Base', 'Base'),
                     'OSGTypeBase.cpp')

    unmoveGVBetaFile(os.path.join(current_dir, 'Source', 'Base', 'Base'),
                     'OSGTypeFactory.h')

    unmoveGVBetaFile(os.path.join(current_dir, 'Source', 'Base', 'Base'),
                     'OSGTypeFactory.cpp')

    unmoveGVBetaFile(os.path.join(current_dir, 'Source', 'System', 'FileIO', 'OBJ'),
                     'OSGOBJSceneFileType.cpp')

    unmoveGVBetaFile(os.path.join(current_dir, 'Source', 'System', 'FileIO', 'WRL'),
                     'OSGVRMLSceneFileType.h')

    unmoveGVBetaFile(os.path.join(current_dir, 'Source', 'System', 'FileIO', 'WRL'),
                     'OSGVRMLSceneFileType.cpp')


class ToolChain:
    def __init__(self, name, **kw):
        self.name = name
        self.env = apply(CreateEnvironment, [], kw)
        
        # add all package include and lib paths
        # ok need to move this in the SConscript files ...
        # only OSGSystem need the image libs.
        # only OSGWindowGLUT need the glut lib.
        for option in _po.getPackageOptions():
            if isinstance(_po.getOption(option), str):
                self.env.Append(CPPPATH = [os.path.join(_po.getOption(option), 'include')])
                self.env.Append(LIBPATHPATH = [os.path.join(_po.getOption(option), 'lib')])

        # add OSG_WITH defines
        if _po.getOption('glut'):
            self.env.Append(CPPDEFINES = ['OSG_WITH_GLUT'])
        if _po.getOption('jpg'):
            self.env.Append(CPPDEFINES = ['OSG_WITH_JPG'])
        if _po.getOption('tif'):
            self.env.Append(CPPDEFINES = ['OSG_WITH_TIF'])
        if _po.getOption('png'):
            self.env.Append(CPPDEFINES = ['OSG_WITH_PNG'])
        if _po.getOption('gif'):
            self.env.Append(CPPDEFINES = ['OSG_WITH_GIF'])
        
        if _po.getOption('qt'):
            #if isinstance(_po.getOption('qt'), str):
            self.env.PrependENVPath('PATH', os.path.join(_po.getOption('qt'), 'bin'))
            self.env['QTCPPPATH'] = [os.path.join(_po.getOption('qt'), 'include')]
            self.env['QTLIBPATH'] = [os.path.join(_po.getOption('qt'), 'lib')]

            if self.env.get('PLATFORM') == 'win32':
                # auto detect qt lib name with version number
                libnames = glob.glob(os.path.join(_po.getOption('qt'), 'lib', 'qt-mt*.lib'))
                if len(libnames) > 0:
                    libname = os.path.basename(libnames[0])
                    libname = libname[:-4]
                    self.env['OSG_WINDOW_QT_LIBS'] = [libname]
                else:
                    print "Couldn't find qt-mt*.lib file!"
            else:
                self.env['OSG_WINDOW_QT_LIBS'] = ['qt-mt']

        if _po.getOption('cg'):
            if isinstance(_po.getOption('cg'), str):
                self.env['CGCPPPATH'] = [os.path.join(_po.getOption('cg'), 'include')]
                self.env['CGLIBPATH'] = [os.path.join(_po.getOption('cg'), 'lib')]
                if self.env.get('PLATFORM') == 'win32':
                    self.env['OSG_CG_LIBS'] = ['Cg', 'CgGL', 'CgFXParser']
                else:
                    self.env['OSG_CG_LIBS'] = ['Cg', 'CgGL', 'CgFXGL']
                    
        if _po.getOption('gv_beta'):
            print 'Compiling with gv beta enabled!'
            self.env.Append(CPPDEFINES = ['OSG_GV_BETA'])
            moveGVBetaFiles()
        else:
            unmoveGVBetaFiles()

        if _po.getOption('invalid_pointer_check'):
            self.env.Append(CPPDEFINES = ['OSG_INVALID_PTR_CHECK'])

        # add include path for OSGConfigured.h file
        self.env.Append(CPPPATH=[Dir(os.path.join('Build', self.name, 'Source', 'Base'))])

    def get_name(self):
        return self.name

    def get_env(self):
        """Returns base environment for this tool chain."""
        return self.env

    def get_env_list(self):
        """Returns list of customized environment configurations
        (debug, opt, etc.) for this tool chain."""
        env = self.env.Copy()
        env['OSG_OBJDIR']  = 'normal'
        env['OSG_LIBSUF']  = ''
        env['OSG_PROGSUF'] = ''
        return [env]

    def is_win32(self):
        return 0

class win32(ToolChain):
    def __init__(self, name):
        ToolChain.__init__(self, name)

        env = self.get_env()

        current_dir = Dir('.').abspath
        supportlibs = ''
        if os.path.exists(os.path.join(current_dir, '..', 'supportlibs')):
            supportlibs = os.path.join(current_dir, '..', 'supportlibs')

        if len(supportlibs) > 0:
            env.AppendENVPath('INCLUDE', supportlibs + os.sep + 'include')
            env.AppendENVPath('LIB', supportlibs + os.sep + 'lib')
            #print 'Added supportlibs path (' + supportlibs + ')'

        slibs = []
        if _po.getOption('jpg'):
            slibs.append('libjpeg')
        if _po.getOption('tif'):
            slibs.append('tif32')
        if _po.getOption('png'):
            slibs.append('libpng')
            slibs.append('zlib')

        env['OSG_BASE_LIBS'] = []
        env['OSG_SYSTEM_LIBS'] = ['opengl32', 'glu32', 'glu32.lib', 'gdi32'] + slibs
        env['OSG_WINDOW_GLUT_LIBS'] = ['glut32', 'opengl32', 'glu32.lib', 'gdi32']
        #env['OSG_WINDOW_QT_LIBS'] = []

        # ws2_32
        env.Append(LINKFLAGS=['/NODEFAULTLIB'],
                   LIBS = ['user32', 'kernel32', 'winmm', 'wsock32'])

        if _po.buildDbg():
            env.Append(LIBS = ['msvcprtd', 'msvcrtd'])
        else:
            env.Append(LIBS = ['msvcprt', 'msvcrt'])

    def is_win32(self):
        return 1

class win32_icl_base(win32):
    def __init__(self, name):
        win32.__init__(self, name)
        env = self.get_env()

        #env.Replace(no_import_lib = 1)

        # icl.py is buggy only looks for version 7.0
        # also need to get the version number.
        # I commented this line out "SCons.Tool.msvc.generate(env)"
        # I don't want the .net include and lib paths.
        # I have 4 compilers on my machine (ok worst case) icl 6.0, msvc 6.0,
        # msvc 7.0, msvc 7.1 actually 5 gcc ;-)
        env.Tool('icl')
        #env.Tool('mslink')
        #env.Tool('mslib')

        # add msvc6 include and lib paths
        import SCons.Tool.msvc
        include_path, lib_path, exe_path = SCons.Tool.msvc._get_msvc6_default_paths("6.0", 0)
        env.PrependENVPath('INCLUDE', include_path)
        env.PrependENVPath('LIB', lib_path)

        # add intel compiler bin, include, lib, path for libmmd.lib
        import SCons.Tool.icl
        iclversions = ['8.1', '8.0', '7.1', '7.0', '6.0', '5.0']
        icltop = None
        iclversion = "600"
        for iclv in iclversions:
            icltop = SCons.Tool.icl.get_intel_compiler_top(iclv)
            if icltop:
                # create a three digit version string
                iclversion = str(int(float(iclv) * 100))
                break
        if icltop:
            #print 'Added compiler path (' + icltop + ')'
            env.PrependENVPath('INCLUDE', os.path.join(icltop, 'Include'))
            env.PrependENVPath('LIB', os.path.join(icltop, 'Lib'))
            env.PrependENVPath('PATH', os.path.join(icltop, 'Bin'))
        else:
            print "Couldn't find icl compiler!"

        #print env['ENV']['INCLUDE']
        #print env['ENV']['LIB']

        env.AppendENVPath('PATH', GetCygwinPath('/bin'))

        env.Append(CXXFLAGS=['-W4',
                             '-Qwd985', '-Qwd530', '-Qwd981', '-Qwd193',
                             '-Qwd444', '-Qwd279',
                             '-Qwe698', '-Qwe47', '-Qwe373', '-Qwe171', '-Qwe373', '-Qwe261'])


        env.Append(CPPDEFINES=win32_defines,
                   CXXFLAGS=['-Qvc6', '-GX', '-Gi-', '-Qansi',
                             '-Qoption,cpp,--new_for_init', '-GR'])

        # XXX HACK need to autodetect the compiler version!
        # '__STDC__'
        env.Append(CPPDEFINES=['__INTEL_COMPILER_VERSION=' + iclversion])

    def get_env_list(self):
        env = self.get_env()

        envs = []

        if _po.buildDbg():
            dbg = env.Copy()
            dbg.Append(CXXFLAGS=['/MDd', '/Od', '/RTC1', '/Z7'],
                       LINKFLAGS=['/DEBUG'],
                       CPPDEFINES=['_DEBUG', 'OSG_DEBUG'])
            dbg['OSG_OBJDIR']  = 'dbg'
            dbg['OSG_LIBSUF']  = 'D'
            dbg['OSG_PROGSUF'] = 'D'
            envs.append(dbg)

        if _po.buildDbgOpt():
            dbg = env.Copy()
            dbg.Append(CXXFLAGS=['/MD', '/Od', '/RTC1', '/Z7'],
                       LINKFLAGS=['/DEBUG'],
                       CPPDEFINES=['_DEBUG', 'OSG_DEBUG'])
            dbg['OSG_OBJDIR']  = 'dbg'
            dbg['OSG_LIBSUF']  = ''
            dbg['OSG_PROGSUF'] = ''
            envs.append(dbg)

        if _po.buildOpt():
            opt = env.Copy()
            opt.Append(CXXFLAGS=['/MD', '/O2'],
                       LINKFLAGS=['/OPT:REF', '/OPT:ICF'],
                       CPPDEFINES=['NDEBUG'])
            opt['OSG_OBJDIR']  = 'opt'
            opt['OSG_LIBSUF']  = ''
            opt['OSG_PROGSUF'] = ''
            envs.append(opt)

        return envs

class win32_icl(win32_icl_base):
    def __init__(self):
        win32_icl_base.__init__(self, 'win32-icl')
        env = self.get_env()

class win32_msvc_base(win32):
    def __init__(self, name):
        win32.__init__(self, name)
        env = self.get_env()

        env.AppendENVPath('PATH', GetCygwinPath('/bin'))

        env.Append(CPPDEFINES=win32_defines)

        env.Append(LINKFLAGS=['/FORCE:MULTIPLE'])

    def get_env_list(self):
        env = self.get_env()

        envs = []

        if _po.buildDbg():
            dbg = env.Copy()
            dbg.Append(CXXFLAGS=['/MDd', '/Od', '/ZI', '/GZ'],
                       LINKFLAGS=['/DEBUG'],
                       CPPDEFINES=['_DEBUG', 'OSG_DEBUG'])
            dbg['OSG_OBJDIR']  = 'dbg'
            dbg['OSG_LIBSUF']  = 'D'
            dbg['OSG_PROGSUF'] = 'D'
            envs.append(dbg)

        if _po.buildDbgOpt():
            dbg = env.Copy()
            dbg.Append(CXXFLAGS=['/MD', '/Od', '/ZI', '/GZ'],
                       LINKFLAGS=['/DEBUG'],
                       CPPDEFINES=['_DEBUG', 'OSG_DEBUG'])
            dbg['OSG_OBJDIR']  = 'dbg'
            dbg['OSG_LIBSUF']  = ''
            dbg['OSG_PROGSUF'] = ''
            envs.append(dbg)

        if _po.buildOpt():
            opt = env.Copy()
            opt.Append(CXXFLAGS=['/MD', '/O2', '/Ob1'],
                       LINKFLAGS=['/OPT:REF', '/OPT:ICF'],
                       CPPDEFINES=['NDEBUG'])
            opt['OSG_OBJDIR']  = 'opt'
            opt['OSG_LIBSUF']  = ''
            opt['OSG_PROGSUF'] = ''
            envs.append(opt)

        return envs

class win32_msvc71(win32_msvc_base):
    def __init__(self):
        win32_msvc_base.__init__(self, 'win32-msvc71')
        env = self.get_env()

        env.Append(CXXFLAGS=['/GX', '/GR', '/Gi', '/FD', '/Zm1200'])

        # add msvc71 include and lib paths
        import SCons.Tool.msvc
        include_path, lib_path, exe_path = SCons.Tool.msvc._get_msvc6_default_paths("7.1", 0)

        env.PrependENVPath('INCLUDE', include_path)
        env.PrependENVPath('INCLUDE', os.path.join(include_path, '..', 'PlatformSDK', 'Include'))
        env.PrependENVPath('LIB', lib_path)
        env.PrependENVPath('LIB', os.path.join(lib_path, '..', 'PlatformSDK', 'Lib'))
        env.PrependENVPath('PATH', exe_path)

class win32_msvc70(win32_msvc_base):
    def __init__(self):
        win32_msvc_base.__init__(self, 'win32-msvc70')
        env = self.get_env()

        env.Append(CXXFLAGS=['/GX', '/GR', '/Gi', '/FD', '/Zm1200'])
        # add msvc71 include and lib paths
        import SCons.Tool.msvc
        include_path, lib_path, exe_path = SCons.Tool.msvc._get_msvc6_default_paths("7.0", 0)

        env.PrependENVPath('INCLUDE', include_path)
        env.PrependENVPath('LIB', lib_path)
        env.PrependENVPath('PATH', exe_path)

class win32_msvc80(win32_msvc_base):
    def __init__(self):
        win32_msvc_base.__init__(self, 'win32-msvc80')
        env = self.get_env()

        env.Append(CXXFLAGS=['/Wp64', '/w44258', '/w44996', '/EHsc', '/GR', '/FD',
                             '/Zm1200', '/Zc:forScope'])

        # add msvc80 include and lib paths
        #import SCons.Tool.msvc
        # doesn't work for 8.0 :-(
        #include_path, lib_path, exe_path = SCons.Tool.msvc._get_msvc6_default_paths("8.0", 0)
        # HACK
        include_path = ['C:/Programme/Microsoft Visual Studio 8/VC/include',
                        'C:/Programme/Microsoft Platform SDK/Include']
        lib_path = ['C:/Programme/Microsoft Visual Studio 8/VC/lib',
                    'C:/Programme/Microsoft Visual Studio 8/SDK/v2.0/lib',
                    'C:/Programme/Microsoft Platform SDK/Lib']
        exe_path = ['C:/Programme/Microsoft Visual Studio 8/Common7/IDE',
                    'C:/Programme/Microsoft Visual Studio 8/VC/bin',
                    'C:/Programme/Microsoft Visual Studio 8/Common7/Tools',
                    'C:/Programme/Microsoft Visual Studio 8/SDK/v2.0/bin',
                    'C:/WINDOWS/Microsoft.NET/Framework/v2.0.50727',
                    'C:/Programme/Microsoft Visual Studio 8/VC/VCPackages']

        env.PrependENVPath('INCLUDE', include_path)
        env.PrependENVPath('LIB', lib_path)
        env.PrependENVPath('PATH', exe_path)

class cygwin_gcc(win32):
    def __init__(self):
        win32.__init__(self, 'cygwin-gcc')
        env = self.get_env()
        env.Tool('mingw')
        env.Tool('mslink')
        env.Append(CPPDEFINES=win32_defines,
                   CXXFLAGS=['-mno-cygwin', '-ftemplate-depth-100'],
                   LINKFLAGS=['-mno-cygwin'],
                   OSG_BASE_LIBS = ['winmm', 'ws2_32'])

class linux_gcc(ToolChain):
    def __init__(self):
        ToolChain.__init__(self, 'linux-gcc')

    def get_env_list(self):
        env = self.get_env()

        slibs = []
        if _po.getOption('jpg'):
            slibs.append('libjpeg')
        if _po.getOption('tif'):
            slibs.append('libtiff')
        if _po.getOption('png'):
            slibs.append('libpng')
            slibs.append('libz')

        env = env.Copy()
        
        env.Append(CXXFLAGS=['-ansi', '-use_readonly_const',
                             '-ftemplate-depth-100'],
                   CPPDEFINES=['_GNU_SOURCE', '_OSG_HAVE_CONFIGURED_H_'],
                   LINKFLAGS = ['-Wl,-s'])

        env['OSG_BASE_LIBS'] = ['pthread', 'dl']
        env['OSG_SYSTEM_LIBS'] = ['GLU', 'GL'] + slibs
        env['OSG_WINDOW_GLUT_LIBS'] = ['glut', 'GL']
        #env['OSG_WINDOW_QT_LIBS'] = []
        env['OSG_WINDOW_X_LIBS'] = []

        env['OSG_OBJDIR'] = 'obj'

        envs = []

        if _po.buildDbg():
            dbg = env.Copy()
            dbg.Append(CXXFLAGS=['-g'],
                       LINKFLAGS=[''],
                       CPPDEFINES=['_DEBUG', 'OSG_DEBUG'])
            dbg['OSG_OBJDIR']  = 'dbg'
            dbg['OSG_LIBDIR']  = 'dbg'
            dbg['OSG_PROGDIR'] = 'dbg'
            envs.append(dbg)

        if _po.buildOpt():
            opt = env.Copy()
            opt.Append(CXXFLAGS=['-O2'],
                       LINKFLAGS=['-s'],
                       CPPDEFINES=[])
            opt['OSG_OBJDIR']  = 'opt'
            opt['OSG_LIBDIR']  = 'opt'
            opt['OSG_PROGDIR'] = 'opt'
            envs.append(opt)

        return envs

class unknown(ToolChain):
    "Specific build type is not known.  Try defaults."
    def __init__(self):
        ToolChain.__init__(self, 'unknown')

def hasICL():
    f = os.popen('icl -help', 'r')
    for line in f.xreadlines():
        if string.find(line, 'Intel') >= 0:
            return 1
    return 0

def SelectToolChain():
    de = DefaultEnvironment()
    if de.get('PLATFORM') == 'cygwin':
        return cygwin_gcc()
    elif de.get('PLATFORM') == 'win32':
        msvs_version = de.get('MSVS_VERSION')
        if _po.getOption('compiler') == 'gcc':
            return cygwin_gcc()
        elif _po.getOption('compiler') == 'icl':
            return win32_icl()
        elif _po.getOption('compiler') == 'msvc70':
            return win32_msvc70()
        elif _po.getOption('compiler') == 'msvc71':
            return win32_msvc71()
        elif _po.getOption('compiler') == 'msvc80':
            return win32_msvc80()
        else:
            print "WARNING: Unsupported MSVS version found: %s.  Trying defaults." % msvs_version
            return unknown()
    else:
        if sys.platform == 'linux2':
            return linux_gcc()
        else:
            print "WARNING: Build toolchain not autodetected.  Trying defaults."
            return unknown()

# Process options.

opts = Options('options.cache', ARGUMENTS)
opts.AddOptions(
    BoolOption('distcc', 'Compile using distcc', 0))
#('QT_LIB', 'Name of the QT library', 'qt')

_po = PlatformOptions(opts)
Export('_po')

tc = SelectToolChain()
print "Detected environment: %s" % tc.get_name()
Export('tc')

env = tc.get_env()
env['BUILD_DIR'] = Dir(os.path.join('Build', tc.get_name()))
env['PREFIX'] = env['BUILD_DIR'].Dir('installed')
Default(env['PREFIX'])

opts.Update(env) # Update the environment with the options.
opts.Save('options.cache', env)
Help(opts.GenerateHelpText(env))

CreateWinHeaders(env)
CreateConfiguredHeader(env)

if env['distcc']:
    distcc = WhereIs('distcc')
    if distcc:
        print "Found distcc: " + distcc
        env['CC']  = ['$(', distcc, '$)', env['CC']]
        env['CXX'] = ['$(', distcc, '$)', env['CXX']]
        env['ENV']['DISTCC_HOSTS'] = os.environ.get('DISTCC_HOSTS')
    else:
        print "Error: distcc not found in PATH"

BuildDir(env['BUILD_DIR'], '.', duplicate=0)

Export('env')
SConscript(dirs=map(
    lambda n: env['BUILD_DIR'].Dir(n),
    ['Source', 'Examples', 'Tools', 'Tutorials']))
