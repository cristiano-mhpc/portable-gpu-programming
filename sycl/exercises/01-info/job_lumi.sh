#!/bin/bash
#SBATCH --job-name=sycl_device_query
#SBATCH --account=project_462001074
#SBATCH --partition=small-g
# #SBATCH --reservation=portgp-2025-wed # This changes every day to -wed, -thu and -fri, valid 09:00 to 17:00
#SBATCH --time=00:05:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=2
#SBATCH --gpus-per-node=2

srun ./a.out 
