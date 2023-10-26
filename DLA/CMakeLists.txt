cmake_minimum_required(VERSION 3.20)

if( NOT DEFINED CMAKE_TOOLCHAIN_FILE AND ENV{CMAKE_TOOLCHAIN_FILE})
    set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

project(DLA_build)
set(CMAKE_CXX_STANDARD 17)
find_package(OpenImageIO CONFIG REQUIRED)
find_package(Boost COMPONENTS filesystem thread)
find_package(fmt CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)


add_executable(DLA)
target_include_directories(DLA PRIVATE include)
target_sources(DLA PRIVATE
        src/main.cpp
        src/Image.cpp
        src/Walker.cpp
        include/Walker.h
        include/Image.h
        include/RGBA.h)
target_link_libraries(DLA PRIVATE fmt::fmt-header-only)
target_link_libraries(DLA PRIVATE OpenImageIO::OpenImageIO Boost::filesystem
Boost::thread)

target_link_libraries(DLA PRIVATE cxxopts::cxxopts)
