#!/bin/bash

#
# Project Hydra
# (C) 2016 Christian Gunderman
#

git submodule init
git submodule update
cmake .
make
./hydra_core/hydra_core_tests

# Kill build if test fails.
if [[ $? != 0 ]]; then
   exit 1
fi
