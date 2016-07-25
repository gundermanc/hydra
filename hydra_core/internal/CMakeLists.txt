# Project Hydra
# (C) 2016 Christian Gunderman
# Core Library Build File

include_directories(../include_private)

# --------------------- Code --------------------- 
# Put testable code in its own library:
# Think Java "package" that we can import into other subprojects
# with target_link_library() and includes in the C/C++ files.
add_library (
    hydra_core_internal
    hydra_service_manager_private.cc)
