make clean
make
./gera_matrizv3 1000 1000
mpirun --hostfile hostfile_ens -np 4 main_matrizv3 1000x1000-mat.map 1000x1000-mat.map 
