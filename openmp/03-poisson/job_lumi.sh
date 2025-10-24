#!/bin/bash
#SBATCH --job-name=slurm-test
#SBATCH --account=project_462001074
#SBATCH --partition=small-g
#SBATCH --reservation=portgp-2025-fri # This changes every day to -wed, -thu and -fri, valid 09:00 to 17:00
#SBATCH --time=00:05:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --gpus-per-node=1

export CRAY_ACC_DEBUG=2 # useful information for debugging on AMD
srun ./poisson.x 2048 1000 
 
# export OMP_DISPLAY_AFFINITY=true #run on cpu
# srun ./poisson.x 2048 1000 
