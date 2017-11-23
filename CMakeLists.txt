cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${PROJECT_SRC})

add_subdirectory(${PROJECT_SRC}/vm)

add_executable(mix_vm ${PROJECT_SRC}/app/main.cpp)
target_link_libraries (mix_vm vm)

add_subdirectory(tests)
