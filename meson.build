project(
  'fractals',
  'c',
  'cpp',
default_options : ['c_std=c11', 'cpp_std=c++17', 'b_lto=True'],
version : '0.1.0',
license : 'GPL-v3'
)

cc = meson.get_compiler('cpp')
ssmod = import('sourceset')
ss = ssmod.source_set()

pymod = import('python')

python_string = 'python3'
if build_machine.system() == 'windows'
    python_string = 'python'
endif

py = pymod.find_installation(python_string, required: false, modules: ['glad'])
if not py.found()
    pip = pymod.find_installation(python_string, required: true, modules: ['pip'])
    r = run_command(pip.path(), '-m', 'pip', 'install', '--user', 'glad')
    if r.returncode() != 0
        error('error while installing glad')
    endif
    
    ninja = find_program('ninja')
    if not ninja.found()
        run_command(pip.path(), '-m', 'pip', 'install', '--user', 'ninja')
    endif
    
    py = pymod.find_installation(python_string, required: true, modules: ['glad'])
endif

deps = [
    dependency('threads', required : true),
    dependency('glfw3', required : true, fallback : ['glfw3', 'glfw_dep']),
    dependency('gl', required : true),
    dependency('glm', required : true, fallback : ['glm','glm_dep']),
    dependency('stb', required : true, fallback : ['stb', 'stb_dep']),
    py.dependency(),
    cc.find_library('dl', required : false),
]

glad_args = [
    '--generator=c',
    '--extensions=GL_EXT_framebuffer_multisample,GL_EXT_texture_filter_anisotropic',
    '--out-path=.',
    '--reproducible',
    '--profile',
    'core',
]

r = run_command(py.path(), '-m', 'glad', glad_args)
if r.returncode() != 0
  message('error while executing glad')
endif
output = r.stdout().strip()
errortxt = r.stderr().strip()

incdir = include_directories('include')

ss.add(
    when: deps,
    if_true: files([
        'src/main.cpp', 
        'src/glad.c',
        'src/gl_handling.cpp',
        'src/window.cpp',
        'src/fractal.cpp',
        'src/koch_snowflake.cpp',
    ])
)

executable(
    'fractals', 
    ss.all_sources(), 
    include_directories : incdir,
    dependencies: ss.all_dependencies(),
)

