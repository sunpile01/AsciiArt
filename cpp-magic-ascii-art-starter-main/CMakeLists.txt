cmake_minimum_required(VERSION 3.10)

# Project name and version
project(ASCIIART VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# Source files
set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/ImageLoaders/BMPLoader.cpp
    ${CMAKE_SOURCE_DIR}/src/ImageLoaders/JPEGLoader.cpp
    ${CMAKE_SOURCE_DIR}/src/ImageLoaders/PNGLoader.cpp
    ${CMAKE_SOURCE_DIR}/include/easyBMP/EasyBMP.cpp
    ${CMAKE_SOURCE_DIR}/include/LodePNG/lodepng.cpp
    ${CMAKE_SOURCE_DIR}/src/Util/Util.cpp
)

# Add the executable
add_executable(ASCIIART ${SOURCES})

# Include directories (adding all subdirectories)
target_include_directories(ASCIIART PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/easyBMP
    ${CMAKE_SOURCE_DIR}/include/JPEGLoader
    ${CMAKE_SOURCE_DIR}/include/LodePNG
)
