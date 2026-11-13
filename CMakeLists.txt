cmake_minimum_required(VERSION 3.10)

project(
    CPU-EMU
    VERSION 1.0
    LANGUAGES CXX
)

file(
    GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(
    ${PROJECT_NAME}
    PRIVATE
    cxx_std_17
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
)
