#!/bin/bash 
cc -O3 -fopenmp poisson.c -o poisson.x
# ftn -O3 -fopenmp helper_functions.F90 poisson.F90 -o poisson.x
