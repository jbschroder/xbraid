# Script for MPI runs, 
#
#  $ mpirun -np K  python3 drive_adv_diff_1D_scriptrun.py
#
# Compile with
#
#  $ python3 drive_adv_diff_1D-setup.py install --prefix=$HOME/.local

import drive_adv_diff_1D
from viz_drive_adv_diff_1D import viz_drive_adv_diff_1D

# Can choose to print help message
print_help = False

# Proof code
# Do another run but with explicit
# Write up 
# - Automate any generation of tables?
# - Note that RP (or PR) must be close to I -- or results suffer 
# - Start off with some theory ala Tzanio?
# - What will degree 2 relaxation do?
#
# How to post-process?
# mpirun -np 2 python3 drive_adv_diff_1D_scriptrun.py  > temp.txt
# egrep "Time: |  iterations" temp.txt


# Choose explicit parametes or implicit
if True:
    discr = [('BE', 'upwind'), ('SDIRK3', 'fourth_diss')]#, ('SDIRK3', 'fourth_diss_sq')]
    
    ## Broad Test 1
    #CWts = [0.8, 1.0, 1.2, 1.6]             # relaxation weights
    #cfs = [2, 4]                            # coarsening factors in time
    #scs = [0, 1, 2]                         # spatial coarsening options 
    #eps = [0]                               # zero diffusion
    #a = [0.5, 1.0, 2.0]                     # advection speed of 1.1

    ## Narrow Test 1
    #CWts = [0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3] # relaxation weights
    #cfs = [4]                                  # coarsening factors in time
    #scs = [0, 1, 2]                            # spatial coarsening options 
    #eps = [0]                                  # zero diffusion
    #a = [0.5, 1.0]                             # advection speed of 1.1

    ## Narrow Test 2
    CWts = [0.55, 0.7, 0.85, 1.0, 1.15, 1.3]   # relaxation weights
    cfs = [2, 4]                               # coarsening factors in time
    scs = [0, 1, 2]                            # spatial coarsening options 
    eps = [0]                                  # zero diffusion
    a = [0.5, 1.0, 1.1333333]                  # advection speed of 1.1


if False:
    discr = [('FE', 'upwind')]#, ('RK4', 'fourth_diss')]
    CWts = [0.4, 0.55, 0.7, 0.85, 1.0, 1.2, 1.4 ]   # relaxation weights
    cfs = [2]                               # coarsening factors in time
    scs = [1, 2]                            # spatial coarsening options 
    eps = [0]                               # zero diffusion
    a = [0.5, 0.8]                          # advection speed of 1.0

# Problem sizes to loop over in (nx, nt) format
problem_sizes = [ (65, 64), (129, 128), (257, 256), (513, 512), (1025, 1024), (2049, 2048), (4097, 4096)]



for (td, ad) in discr:
    for ee in eps:
        for aa in a:
            for cf in cfs:
                for CWt in CWts:
                    for sc in scs:

                        print("\n\n ---- Time: %s,  space: %s,  eps: %1.2e,  a: %1.2e,  cf: %d,  CWt: %1.2e,  sc: %d ---- \n"%(td, ad, ee, aa, cf, CWt, sc))
                        for (nx, nt) in problem_sizes:
                            core, app = drive_adv_diff_1D.InitCoreApp(print_help=print_help, ml=15, nu=1, nu0=1,
                                                                      CWt=CWt, skip=0, nx=nx, ntime=nt, eps=ee, 
                                                                      a=aa, tol=1e-6, cf=cf, mi=30, sc=sc, fmg=0, 
                                                                      advect_discr=ad, time_discr=td)
                        
                            if print_help == False:
                                drive_adv_diff_1D.run_Braid(core, app)
                        
                            #viz_drive_adv_diff_1D()




