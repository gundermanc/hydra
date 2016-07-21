# Project Hydra
# (C) 2016 Christian Gunderman
# Command Line Application Build File

# --------------------- Entry Point --------------------- 
# Our non-testable entry point:
# This produces an executable called hydra
# which has our main() method. We then link it to the library with our testable
# code.
add_executable (
    hydra
    main.cc)
target_link_libraries(
    hydra
    hydra_core)