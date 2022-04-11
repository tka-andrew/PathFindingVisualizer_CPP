cmake_minimum_required(VERSION 3.10)

# set the project name
project(PathFindingVisualizer VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add the executable
add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(external/wxWidgets-3.1.6)

target_link_libraries(${PROJECT_NAME} wx::net wx::core wx::base)