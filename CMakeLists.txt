# Project Hydra
# (C) 2016 Christian Gunderman
# Root Build File

# --------------------- Prereqs --------------------- 
# CMAKE version and Project Name
cmake_minimum_required (VERSION 2.8.7)
project (Hydra)
include_directories(include)

# --------------------- Tests --------------------- 
# Stuff needed by Google Test, just copy paste this.
include(extern/googletest/cmake/internal_utils.cmake)
config_compiler_and_linker()
link_directories(${gtest_BINARY_DIR}/src)

# Instruct CMAKE to build googletest code and add it's headers
# to our include paths for our compilers.
add_subdirectory (extern/googletest)
include_directories (${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# ---------- Operating System Dependencies ----------
add_subdirectory(hydra_osdeps)

# --------------------- Core Lib -------------------- 
add_subdirectory(hydra_core)


# --------------------- Main App -------------------- 
add_subdirectory(hydra)