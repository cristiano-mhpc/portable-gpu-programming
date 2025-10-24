#!/bin/bash 
cc -O3 -fopenmp axpy.c -o axpy.x
# ftn -O3 -fopenmp helper_functions.F90 axpy.F90 -o axpy.x
