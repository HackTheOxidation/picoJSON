cmake_minimum_required(VERSION 3.20)

project(picoJSON VERSION 0.1.0)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

set(CMAKE_CONFIGURATION_TYPES Debug Release)

add_library(picoJSON_compiler_flags INTERFACE)
target_compile_options(picoJSON_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused;-Wconversion;-Wpedantic;-Werror;-std=c++23>"
  "$<${msvc_cxx}:/W4;/WX;/std:c++22>"
)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -O0 -fsanitize=address,memory,thread,undefined -fsanitize-memory-track-origins")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")

file(GLOB SRC_FILES src/*.cpp)
add_library(picoJSON SHARED ${SRC_FILES})
include_directories(picoJSON include)
target_link_libraries(picoJSON PUBLIC picoJSON_compiler_flags)
