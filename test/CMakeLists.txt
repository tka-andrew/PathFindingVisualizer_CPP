# REFERENCE: https://www.youtube.com/watch?v=Lp1ifh9TuFI
cmake_minimum_required(VERSION 3.10)

set(This UnitTests)

set (Sources
    AlgorithmTest.cpp
)

set (SourcesToBeTested
    ${CMAKE_SOURCE_DIR}/src/pathFindingAlgorithms.cpp
)

set (HeaderDirectoryToBeTested
    ${CMAKE_SOURCE_DIR}/src
)

# REFERENCE: https://docs.wxwidgets.org/3.0/page_libs.html
# REFERENCE: https://docs.wxwidgets.org/trunk/overview_cmake.html
# adv component is needed for wxGrid libraries
find_package(wxWidgets REQUIRED COMPONENTS net core base adv)
include(${wxWidgets_USE_FILE})

add_executable(${This} ${Sources} ${SourcesToBeTested})

target_link_libraries(${This} PUBLIC
    gtest_main # provided by GoogleTest which pulls in a main program
    ${wxWidgets_LIBRARIES}
)

target_include_directories(${This} PUBLIC
    ${HeaderDirectoryToBeTested}
)

add_test(
    NAME {This}
    COMMAND {This}
)