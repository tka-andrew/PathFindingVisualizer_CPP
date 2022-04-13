cmake_minimum_required(VERSION 3.10)

# set the project name
project(PathFindingVisualizer VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# REFERENCE: https://docs.wxwidgets.org/trunk/overview_cmake.html
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

# add the executable
add_executable(${PROJECT_NAME} src/main.cpp)

# REFERENCE: https://docs.wxwidgets.org/trunk/overview_cmake.html
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})