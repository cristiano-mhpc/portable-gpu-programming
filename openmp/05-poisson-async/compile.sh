#!/bin/bash 
cc -O3 -fopenmp poisson.c -DTRACE -lroctx64 -o poisson.x

# ftn -O3 -fopenmp helper_functions.F90 poisson.F90 -DTRACE -lroctx64 -o poisson.x
