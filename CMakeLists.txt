# Simple Cross Platform C++ Example
# (C) 2016 Christian Gunderman

# --------------------- Prereqs --------------------- 
# CMAKE version and Project Name
cmake_minimum_required (VERSION 2.8.7)
project (Example)


# --------------------- Code --------------------- 
# Put testable code in its own library:
# Think Java "package" that we can import into other subprojects
# with target_link_library() and includes in the C/C++ files.
add_library (
    example_lib
    myalgo.cc)


# --------------------- Entry Point --------------------- 
# Our non-testable entry point:
# This produces an executable called example
# which has our main() method. We then link it to the library with our testable
# code.
add_executable (
    example
    main.cc)
target_link_libraries(
    example
    example_lib)


# --------------------- Tests --------------------- 
# Stuff needed by Google Test, just copy paste this.
include(googletest/cmake/internal_utils.cmake)
config_compiler_and_linker()
link_directories(${gtest_BINARY_DIR}/src)

# Instruct CMAKE to build googletest code and add it's headers
# to our include paths for our compilers.
add_subdirectory (googletest)
include_directories (${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


# Create a new executable example_lib_tests that we can execute to
# run our tests. It runs the tests in myalgo_test.cc using the code
# from the gtest library and gtest_main library provided by GoogleTest
# that have the application entry point.
add_executable (
    example_lib_tests
    myalgo_test.cc)
target_link_libraries (example_lib_tests example_lib)
target_link_libraries (example_lib_tests gtest gtest_main)
