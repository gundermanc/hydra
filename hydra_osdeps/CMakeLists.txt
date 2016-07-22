# Project Hydra
# (C) 2016 Christian Gunderman
# Operating System Dependencies Library Build File

include_directories(../include_private)

# --------------------- Code --------------------- 
# Put testable code in its own library:
# Think Java "package" that we can import into other subprojects
# with target_link_library() and includes in the C/C++ files.
add_library (
    hydra_osdeps
    SHARED
    hydra_fileio.cc
    hydra_loader.cc)

# --------------------- Tests --------------------- 
# Create a new executable hydra_core_tests that we can execute to
# run our tests. It runs the tests in myalgo_test.cc using the code
# from the gtest library and gtest_main library provided by GoogleTest
# that have the application entry point.
add_executable (
    hydra_osdeps_tests
    hydra_osdeps_test.cc)
target_link_libraries (hydra_osdeps_tests hydra_osdeps)
target_link_libraries (hydra_osdeps_tests gtest gtest_main)
