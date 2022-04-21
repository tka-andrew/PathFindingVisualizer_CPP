cmake_minimum_required(VERSION 3.10)

# set the project name
project(PathFindingVisualizer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing() # To tell CMake that we are going to have unit tests

# REFERENCE: https://answers.opencv.org/question/194036/how-to-enable-multi-thread-in-cmake-centos/
# to use multi threading, this liune is needed
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread") 

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

# REFERENCE: https://www.youtube.com/watch?v=ED-WUk440qc&list=PLalVdRk2RC6o5GHu618ARWh0VO0bFlif4&index=3
# DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed ${GIT_SUBMOD_RESULT}, please check")
        endif()
    endif()
endif()

# CHECK ALL THE SUBMODULES
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/thirdparty/googletest/CMakeLists.txt")
    message(FATAL_ERROR "The googletest submodule was not downloaded! GIT_SUBMODULE was turned off or failed!")
endif()

add_subdirectory(thirdparty/googletest)

# REFERENCE: https://docs.wxwidgets.org/trunk/overview_cmake.html
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

add_subdirectory(test)