cmake_minimum_required(VERSION 3.16)

project(Curserd VERSION 0.0.1 LANGUAGES CXX)

add_library(Curserd INTERFACE)

target_compile_features(Curserd INTERFACE cxx_std_20)
target_include_directories(Curserd INTERFACE include)

enable_testing()
add_subdirectory(tests)
