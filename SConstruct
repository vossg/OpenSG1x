import dumbdbm
import fnmatch
import os.path
import string

SConsignFile(dbm_module=dumbdbm)
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

def GetWinPath(path):
    f = os.popen('cygpath -w -p ' + path, 'r')
    for wpath in f.xreadlines():
        break
    # remove line feed
    if wpath[-1:] == '\n':
        wpath = wpath[:len(wpath)-1]
    return wpath

Export('GetWinPath')

win32_defines = ['WIN32', '_WINDOWS', 'WINVER=0x0400', '_WIN32_WINDOWS=0x0410',
                 '_WIN32_WINNT=0x0400', 'OSG_DEFAULT_LOG_LEVEL=2',
                 'OSG_DEFAULT_LOG_TYPE=2',
                 'STRICT', 'NOMINMAX']

# 'WIN32_LEAN_AND_MEAN'

# ok we need to add some kind of configure for creating the OSGConfigured.h header file.
# '_OSG_HAVE_CONFIGURED_H_'

class ToolChain:
    def __init__(self, name, **kw):
        self.name = name
        self.env = apply(Environment, [], kw)

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

class win32_icl_base(ToolChain):
    def __init__(self, name):
        ToolChain.__init__(self, name)
        env = self.get_env()
        
        env.Replace(no_import_lib = 1)
        
        # add msvc6 include and lib paths
        import SCons.Tool.msvc
        include_path, lib_path, exe_path = SCons.Tool.msvc._get_msvc6_default_paths("6.0", 0)
        env.PrependENVPath('INCLUDE', include_path)
        env.PrependENVPath('LIB', lib_path)

        # icl.py is buggy only looks for version 7.0
        # also need to get the version number.
        # I commented this line out "SCons.Tool.msvc.generate(env)"
        # I don't want the .net include and lib paths.
        # I have 4 compilers on my machine (ok worst case) icl 6.0, msvc 6.0,
        # msvc 7.0, msvc 7.1 actually 5 gcc ;-)
        env.Tool('icl')
        #env.Tool('mslink')
        #env.Tool('mslib')

        # we need to do this via Configure()
        # glut
        #env.AppendENVPath('INCLUDE', 'D:\cygwin\usr\software\glut-3.7\WIN32\include')
        #env.AppendENVPath('LIB', 'D:\cygwin\usr\software\glut-3.7\WIN32\lib')

        #print env['ENV']['INCLUDE']
        #print env['ENV']['LIB']

        # XXX HACK
        #env.AppendENVPath('PATH', 'C:/cygwin/bin')
        env.AppendENVPath('PATH', GetWinPath('/bin'))

        env.Append(CXXFLAGS=['-W4',
                             '-Qwd985', '-Qwd530', '-Qwd981', '-Qwd193',
                             '-Qwd444', '-Qwd279',
                             '-Qwe698', '-Qwe47', '-Qwe373', '-Qwe171', '-Qwe373', '-Qwe261'])


        env.Append(CPPDEFINES=win32_defines,
                   CXXFLAGS=['-Qvc6', '-GX', '-Gi-', '-Qansi',
                             '-Qoption,cpp,--new_for_init', '-GR'])

        # XXX HACK need to autodetect the compiler version!
        # '__STDC__'
        env.Append(CPPDEFINES=['__INTEL_COMPILER_VERSION=600'])

    def get_env_list(self):
        env = self.get_env()
        
        dbg = env.Copy()
        dbg.Append(CXXFLAGS=['/MDd', '/Od', '/RTC1', '/Z7'],
                   LINKFLAGS=['/DEBUG'],
                   CPPDEFINES=['_DEBUG'])
        dbg['OSG_OBJDIR']  = 'dbg'
        dbg['OSG_LIBSUF']  = 'D'
        dbg['OSG_PROGSUF'] = 'D'

        opt = env.Copy()
        opt.Append(CXXFLAGS=['/MD', '/O2'],
                   LINKFLAGS=['/OPT:REF', '/OPT:ICF'],
                   CPPDEFINES=['NDEBUG'])
        opt['OSG_OBJDIR']  = 'opt'
        opt['OSG_LIBSUF']  = ''
        opt['OSG_PROGSUF'] = ''

        return [dbg, opt]

class win32_icl(win32_icl_base):
    def __init__(self):
        win32_icl_base.__init__(self, 'win32-icl')
        env = self.get_env()

class win32_msvc_base(ToolChain):
    def __init__(self, name):
        ToolChain.__init__(self, name)
        env = self.get_env()
        
        # XXX HACK
        #env.AppendENVPath('PATH', 'C:/cygwin/bin')
        env.AppendENVPath('PATH', GetWinPath('/bin'))

        env.Append(CPPDEFINES=win32_defines,
                   CXXFLAGS=['/GX', '/GR'])

    def get_env_list(self):
        env = self.get_env()
        
        dbg = env.Copy()
        dbg.Append(CXXFLAGS=['/MDd', '/Od', '/RTC1', '/Z7'],
                   LINKFLAGS=['/DEBUG'],
                   CPPDEFINES=['_DEBUG'])
        dbg['OSG_OBJDIR']  = 'dbg'
        dbg['OSG_LIBSUF']  = 'D'
        dbg['OSG_PROGSUF'] = 'D'

        opt = env.Copy()
        opt.Append(CXXFLAGS=['/MD', '/O2', '/GS'],
                   LINKFLAGS=['/OPT:REF', '/OPT:ICF'],
                   CPPDEFINES=['NDEBUG'])
        opt['OSG_OBJDIR']  = 'opt'
        opt['OSG_LIBSUF']  = ''
        opt['OSG_PROGSUF'] = ''

        return [dbg, opt]

class win32_msvc71(win32_msvc_base):
    def __init__(self):
        win32_msvc_base.__init__(self, 'win32-msvc71')

class win32_msvc70(win32_msvc_base):
    def __init__(self):
        win32_msvc_base.__init__(self, 'win32-msvc70')

class cygwin_gcc(ToolChain):
    def __init__(self):
        ToolChain.__init__(self, 'cygwin-gcc')
        env = self.get_env()
        env.Append(CPPDEFINES=win32_defines,
                   CXXFLAGS=['-mno-cygwin'],
                   LINKFLAGS=['-mno-cygwin'])

class unknown(ToolChain):
    "Specific build type is not known.  Try defaults."
    def __init__(self):
        ToolChain.__init__(self, 'unknown')

def hasICL():
    f = os.popen('icl -help', 'r')
    for line in f.xreadlines():
        break
    if string.find(line, 'Intel') >= 0:
        return 1
    return 0

def SelectToolChain():
    de = DefaultEnvironment()
    if de.get('PLATFORM') == 'cygwin':
        return cygwin_gcc()
    elif de.get('PLATFORM') == 'win32':
        msvs_version = de.get('MSVS_VERSION')
        
        if hasICL(): # is there a better way testing this?
            return win32_icl()
        elif msvs_version == '7.1':
            return win32_msvc71()
        elif msvs_version == '7.0':
            return win32_msvc70()
        else:
            print "WARNING: Unsupported MSVS version found: %s.  Trying defaults." % msvs_version
            return unknown()
    else:
        print "WARNING: Build toolchain not autodetected.  Trying defaults."
        return unknown()

tc = SelectToolChain()
print "Detected environment: %s" % tc.get_name()
Export('tc')

env = tc.get_env()
env['BUILD_DIR'] = Dir(os.path.join('Build', tc.get_name()))
env['PREFIX'] = env['BUILD_DIR'].Dir('installed')
Default(env['PREFIX'])

BuildDir(env['BUILD_DIR'], '.', duplicate=0)

Export('env')
SConscript(dirs=map(
    lambda n: env['BUILD_DIR'].Dir(n),
    ['Source', 'Examples']))
