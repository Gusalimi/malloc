#!/bin/sh

export LD_LIBRARY_PATH=$PWD
# export LD_INSERT_LIBRARIES=$PWD/libft_malloc_x86_64_Darwin.so
# export LD_FORCE_FLAT_NAMESPACE=1
# export LD_PRINT_WARNINGS=1
#export DYLD_PRINT_LIBRARIES=1
$@

