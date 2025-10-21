cmake_minimum_required(VERSION 3.10)
project(maple)

set(CMAKE_CXX_STANDARD 17)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(maple src/main.cpp 
                     src/raster.cpp
                     src/camera.cpp
                     src/objects.cpp
                     src/load.cpp
                          )

target_link_libraries(maple ${SDL2_LIBRARIES})
