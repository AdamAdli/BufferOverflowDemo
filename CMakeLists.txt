cmake_minimum_required(VERSION 3.8.0)

project(lab1 C CXX)

# Compiler Options
add_compile_options(-fno-stack-protector)
add_compile_options(-Wno-format-security)

# Link pthread library.
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
link_libraries(Threads::Threads)

# Executable.
add_executable(demo_exploit demo_exploit.c)
add_executable(demo_target demo_target.c demo_setup.c)