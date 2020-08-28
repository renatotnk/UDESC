make clean
make
./gera_matrizv3 100 200
./gera_matrizv3 200 100
mpirun --hostfile hostfile_ens -np 4 main_matrizv3 100x200-mat.map 200x100-mat.map 
