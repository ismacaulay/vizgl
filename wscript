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
        '-Wall',
        '-Werror',

        '-s', 'WASM=1',
        '-s', 'ALLOW_MEMORY_GROWTH=1',
        # '-s', '''EXPORTED_FUNCTIONS=["_createMesh"] ''',
        # '-s', '''EXTRA_EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap'] ''',
        '-O3',
    ]

    conf.env.LINKFLAGS = [

    ]

def build(bld):
    bld.recurse('src')
