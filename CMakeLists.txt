cmake_minimum_required(VERSION 3.5)
project(eCMD VERSION 0.1.0 LANGUAGES C CXX)

if($ENV{eCMD_BUILD_EXAMPLES})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif()


file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS  "libBuild/src/*.cpp")

if(NOT TARGET eCMD)
    add_library(eCMD SHARED ${SOURCE_FILES})
    target_compile_features(eCMD PRIVATE cxx_std_20)
    target_include_directories(eCMD PUBLIC libBuild/hdr)
endif()


message(STATUS "eCMD build examples: " $ENV{eCMD_BUILD_EXAMPLES})

if($ENV{eCMD_BUILD_EXAMPLES})
    add_subdirectory(buildtest)
endif()