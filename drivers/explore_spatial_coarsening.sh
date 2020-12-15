
# Test 1
echo " Classic Heat Equation, Forward Euler, 2nd order FD in Space"
echo " Space-Time Problem: 33x33 by 1024"
echo " "
echo " Test 1: Coarsen by 2 in space, and 2 in time ==> CFL changes on coarse-grids"
echo "   Command: ./drive-diffusion-2D -scoarsenCFL 1 0.4999 -expl -scoarsen 2 -nt 1024 -cf 2 -cfl 0.4 -nx 33 33"
mpirun -np 2 ./drive-diffusion-2D -pgrid 1 1 2 -scoarsenCFL 1 0.4999999 -expl -scoarsen 2 -nt 1024 -cf 2 -cfl 0.4 -nx 33 33  | egrep "Braid:|scheme        |expl  "
echo " "
echo " Test 2: Coarsen by 2 in space, and 4 in time ==> CFL FIXED on all grids ==> Improves Convergence" 
echo "   Command: ./drive-diffusion-2D -scoarsenCFL 1 0.4999 -expl -scoarsen 2 -nt 1024 -cf 4 -cfl 0.4 -nx 33 33"
mpirun -np 2 ./drive-diffusion-2D -pgrid 1 1 2 -scoarsenCFL 1 0.4999999 -expl -scoarsen 2 -nt 1024 -cf 4 -cfl 0.4 -nx 33 33  | egrep "Braid:|scheme        |expl  "
echo " "
echo " Test 3: Coarsen by 2 in space, and 4 in time AND change fine-grid CFL from 0.4 to 0.49 ==> Convergenence DEGRADES a lot" 
echo "   Command: ./drive-diffusion-2D -scoarsenCFL 1 0.4999 -expl -scoarsen 2 -nt 1024 -cf 4 -cfl 0.49 -nx 33 33"
mpirun -np 2 ./drive-diffusion-2D -pgrid 1 1 2 -scoarsenCFL 1 0.4999999 -expl -scoarsen 2 -nt 1024 -cf 4 -cfl 0.49 -nx 33 33  | egrep "Braid:|scheme        |expl  "

