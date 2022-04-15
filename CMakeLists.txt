cmake_minimum_required(VERSION 3.10)

# set the project name
project(PathFindingVisualizer VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# REFERENCE: https://answers.opencv.org/question/194036/how-to-enable-multi-thread-in-cmake-centos/
# to use multi threading, this liune is needed
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread") 

# REFERENCE: https://docs.wxwidgets.org/3.0/page_libs.html
# REFERENCE: https://docs.wxwidgets.org/trunk/overview_cmake.html
# adv component is needed for wxGrid libraries
find_package(wxWidgets REQUIRED COMPONENTS net core base adv)
include(${wxWidgets_USE_FILE})

file( GLOB cppFILES
    src/main.cpp
    src/mainFrame.cpp
    src/panels.cpp
    src/pathFindingAlgorithms.cpp
)

# add the executable
add_executable(${PROJECT_NAME} ${cppFILES})

# REFERENCE: https://docs.wxwidgets.org/trunk/overview_cmake.html
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})