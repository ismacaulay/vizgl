import sys

top = '.'
out = '.build'

tools = 'compiler_cxx compiler_c'

def options(opt):
    opt.load(tools)

def configure(conf):
    conf.load(tools)

    conf.env.CXXFLAGS = [
        '-std=c++17',
        # '-Wall',
        # '-Werror',
        # '-Wno-int-to-pointer-cast',
        '-s', 'WASM=1',
        '-s', 'USE_SDL=2',
        '-s', 'ALLOW_MEMORY_GROWTH=1',
        '-O3',
    ]

    conf.env.LINKFLAGS = [
        # '-lglfw',
        '-s', 'USE_SDL=2',
    ]

    # if sys.platform == 'darwin':
    #     conf.env.FRAMEWORK = ['OpenGL']
    #     conf.env.DEFINES = [
    #         'GL_SILENCE_DEPRECATION',
    #         # '__gl_h_',
    #         # 'GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED',
    #     ]

    # elif sys.platform == 'linux':
    #     conf.env.LINKFLAGS.extend([
    #         '-lGL',
    #         '-lGLEW',
    #         '-ldl',
    #     ])

def build(bld):
    bld.recurse('src')
