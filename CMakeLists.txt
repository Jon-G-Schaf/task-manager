cmake_minimum_required(VERSION 3.16)
project(TaskManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 COMPONENTS Widgets QUIET)
if(NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
endif()

add_executable(taskmanager main.cpp)

if(Qt6_FOUND)
    target_link_libraries(taskmanager Qt6::Widgets)
else()
    target_link_libraries(taskmanager Qt5::Widgets)
endif()
