# Script for MPI runs of Cython code 
#
#  $ mpirun -np K  python3 drive_adv_diff_1D_run.py
#
# Compile with
#
#  $ python3 drive_adv_diff_1D-setup.py install --prefix=$HOME/.local


import drive_adv_diff_1D

# Can choose to print help message
print_help = False

core, app = drive_adv_diff_1D.InitCoreApp(print_help=print_help, ml=15, nu=1, nu0=1,
                                          CWt=1.0, skip=0, nx=513, ntime=512, eps=0.0, 
                                          a=1.0, tol=1e-6, cf=4, mi=30, sc=2, fmg=0, 
                                          access_level=2, advect_discr='fourth_diss', 
                                          diff_discr='second_order', time_discr='SDIRK3')

if print_help == False:
    drive_adv_diff_1D.run_Braid(core, app)
     
# Uncomment to run simple visualization script
if False:
    from viz_drive_adv_diff_1D import viz_drive_adv_diff_1D
    viz_drive_adv_diff_1D()
    # remove viz output files
    import os
    os.system('rm *.out*')

