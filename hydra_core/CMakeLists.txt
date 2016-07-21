# Project Hydra
# (C) 2016 Christian Gunderman
# Core Library Build File

# --------------------- Code --------------------- 
# Put testable code in its own library:
# Think Java "package" that we can import into other subprojects
# with target_link_library() and includes in the C/C++ files.
add_library (
    hydra_core
    SHARED
    hydra_core.cc)

# --------------------- Tests --------------------- 
# Create a new executable hydra_core_tests that we can execute to
# run our tests. It runs the tests in myalgo_test.cc using the code
# from the gtest library and gtest_main library provided by GoogleTest
# that have the application entry point.
add_executable (
    hydra_core_tests
    hydra_core_test.cc)
target_link_libraries (hydra_core_tests hydra_core)
target_link_libraries (hydra_core_tests gtest gtest_main)
