cmake_minimum_required(VERSION 3.6)
project(Bubble_Creatures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find SDL
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(SOURCE_FILES src/main.cpp src/Population.cpp include/Population.h src/Bubble.cpp include/Bubble.h src/Screen.cpp include/Screen.h src/Food.cpp include/Food.h src/FoodSupply.cpp include/FoodSupply.h)
add_executable(Bubble_Creatures ${SOURCE_FILES})
target_link_libraries(Bubble_Creatures ${SDL2_LIBRARY})