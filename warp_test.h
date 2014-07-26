
/*BHEADER**********************************************************************
 * Copyright (c) 2013,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * This file is part of WARP.  See file COPYRIGHT for details.
 *
 * WARP is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 ***********************************************************************EHEADER*/

/** \file warp.h
 * \brief Define headers for user interface routines.
 *
 * This file contains routines used to allow the user to initialize, run
 * and get and set warp. 
 */

#ifndef warp_test_HEADER
#define warp_test_HEADER

#include "warp.h"
#include "_warp.h"

#ifdef __cplusplus
extern "C" {
#endif


/*--------------------------------------------------------------------------
 * Routines for user to test interface routines
 *--------------------------------------------------------------------------*/
/** \defgroup warptest Warp user test routines
 *  
 *  These sanity check routines to help a user test their Warp code
 *
 *  @{
 */

/**
 * Test Init, Write and Free\n
 * A vector is initialized at time t, written, and then free-d
 **/
warp_Int
warp_TestInitWrite( warp_App              app,     /**< User defined App structure */
                    MPI_Comm              comm_x,  /**< Spatial communicator */
                    FILE                 *fp,      /**< File pointer (could be stdout or stderr) for log messages*/
                    warp_Real             t,       /**< Time value to test init with */
                    warp_PtFcnInit        init,    /**< Initialize a warp_Vector function on finest temporal grid*/
                    warp_PtFcnWrite       write,   /**< Write temporal state warp_Vector (can be NULL for no writing)*/
                    warp_PtFcnFree        free     /**< Free a temporal state warp_Vector*/
                    );

 /**
  * Test Clone\n
  * A vector is initialized at time t, cloned, and both vectors are written.
  * Then both vectors are free-d.  The user is to check the output to see if 
  * it is identical.
  **/
warp_Int
warp_TestClone( warp_App              app,         /**< User defined App structure */
                MPI_Comm              comm_x,      /**< Spatial communicator */
                FILE                 *fp,          /**< File pointer (could be stdout or stderr) for log messages*/
                warp_Real             t,           /**< Time value to test clone with  */
                warp_PtFcnInit        init,        /**< Initialize a warp_Vector function on finest temporal grid*/
                warp_PtFcnWrite       write,       /**< Write temporal state warp_Vector (can be NULL for no writing)*/
                warp_PtFcnFree        free,        /**< Free a temporal state warp_Vector*/
                warp_PtFcnClone       clone        /**< Clone a temporal state warp_Vector */
                );



 /**
  * Test Sum\n
  * A vector is initialized at time t, cloned, and then these two vectors
  * are summed a few times, with the results written.  The vectors are then free-d.
  * The user is to check that the output matches the sum of the two original vectors.
  **/
warp_Int
warp_TestSum( warp_App              app,         /**< User defined App structure */
              MPI_Comm              comm_x,      /**< Spatial communicator */
              FILE                 *fp,          /**< File pointer (could be stdout or stderr) for log messages*/
              warp_Real             t,           /**< Time value to test Sum with  (used to initialize the vectors*/
              warp_PtFcnInit        init,        /**< Initialize a warp_Vector function on finest temporal grid*/
              warp_PtFcnWrite       write,       /**< Write temporal state warp_Vector (can be NULL for no writing)*/
              warp_PtFcnFree        free,        /**< Free a temporal state warp_Vector*/
              warp_PtFcnClone       clone,       /**< Clone a temporal state warp_Vector */
              warp_PtFcnSum         sum          /**< Compute vector sum of two temporal states*/
              );

/**
 * Test Dot.  A vector is initialized at time t and then cloned.  Various
 * dot products like <3 v, v>/<v, v> are computed with known output, e.g.,
 * <3 v, v>/<v, v> must equal 3.  If all the tests pass, then 1 is returned.
 *
 * Returns 0 if the tests fail
 * Returns 1 if the tests pass
 * Check the log messages to see details of which tests failed.
 **/
warp_Int
warp_TestDot( warp_App              app,         /**< User defined App structure */
              MPI_Comm              comm_x,      /**< Spatial communicator */
              FILE                 *fp,          /**< File pointer (could be stdout or stderr) for log messages*/
              warp_Real             t,           /**< Time value to test Dot with  (used to initialize the vectors*/
              warp_PtFcnInit        init,        /**< Initialize a warp_Vector function on finest temporal grid*/
              warp_PtFcnFree        free,        /**< Free a temporal state warp_Vector*/
              warp_PtFcnClone       clone,       /**< Clone a temporal state warp_Vector */
              warp_PtFcnSum         sum,         /**< Compute vector sum of two temporal states*/
              warp_PtFcnDot         dot          /**< Compute dot product of two temporal states*/
              );
              
/**
 * A vector is initialized at time t, packed into a buffer, then unpacked from a buffer.
 * The unpacked result must equal the original vector.  
 *
 * Returns 0 if the tests fail
 * Returns 1 if the tests pass
 * Check the log messages to see details of which tests failed.
 **/
warp_Int
warp_TestBuf( warp_App              app,         /**< User defined App structure */
              MPI_Comm              comm_x,      /**< Spatial communicator */
              FILE                 *fp,          /**< File pointer (could be stdout or stderr) for log messages*/
              warp_Real             t,           /**< Time value to test Buffer routines  (used to initialize the vectors*/
              warp_PtFcnInit        init,        /**< Initialize a warp_Vector function on finest temporal grid*/
              warp_PtFcnFree        free,        /**< Free a temporal state warp_Vector*/
              warp_PtFcnSum         sum,         /**< Compute vector sum of two temporal states*/
              warp_PtFcnDot         dot,         /**< Compute dot product of two temporal states*/
              warp_PtFcnBufSize     bufsize,     /**< Computes size for MPI buffer for one */
              warp_PtFcnBufPack     bufpack,     /**< Packs MPI buffer to contain one temporal state*/
              warp_PtFcnBufUnpack   bufunpack    /**< Unpacks MPI buffer containing one temporal state*/
              );

/**
 * A vector is initialized at time t, and various sanity checks on the spatial
 * coarsening and refinement routines are run.
 *
 * Returns 0 if the tests fail
 * Returns 1 if the tests pass
 * Check the log messages to see details of which tests failed.
 **/
warp_Int
warp_TestCoarsenRefine( warp_App          app,         /**< User defined App structure */
                        MPI_Comm          comm_x,      /**< Spatial communicator */
                        FILE             *fp,          /**< File pointer (could be stdout or stderr) for log messages*/
                        warp_Real         t,           /**< Time value to initialize vector */
                        warp_Real         fdt,         /**< Fine time step value that you spatially coarsen from */
                        warp_Real         cdt,         /**< Coarse time step value that you coarsen to */
                        warp_PtFcnInit    init,        /**< Initialize a warp_Vector function on finest temporal grid*/
                        warp_PtFcnWrite   write,       /**< Write temporal state warp_Vector (can be NULL for no writing)*/
                        warp_PtFcnFree    free,        /**< Free a temporal state warp_Vector*/
                        warp_PtFcnClone   clone,       /**< Clone a temporal state warp_Vector */
                        warp_PtFcnSum     sum,         /**< Compute vector sum of two temporal states*/
                        warp_PtFcnDot     dot,         /**< Compute dot product of two temporal states*/
                        warp_PtFcnCoarsen coarsen,     /**< Spatially coarsen a vector */
                        warp_PtFcnRefine  refine       /**< Spatially refine a vector */
                        );
/**
 * Runs all of the individual warp_Test* routines
 *
 * Returns 0 if the tests fail
 * Returns 1 if the tests pass
 * Check the log messages to see details of which tests failed.
 **/
warp_Int
warp_TestAll( warp_App             app,         /**< User defined App structure */
              MPI_Comm             comm_x,      /**< Spatial communicator */
              FILE                *fp,          /**< File pointer (could be stdout or stderr) for log messages*/
              warp_Real            t,           /**< Time value to initialize vector */
              warp_Real            fdt,         /**< Fine time step value that you spatially coarsen from */
              warp_Real            cdt,         /**< Coarse time step value that you coarsen to */
              warp_PtFcnInit       init,        /**< Initialize a warp_Vector function on finest temporal grid*/
              warp_PtFcnFree       free,        /**< Free a temporal state warp_Vector*/
              warp_PtFcnClone      clone,       /**< Clone a temporal state warp_Vector */
              warp_PtFcnSum        sum,         /**< Compute vector sum of two temporal states*/
              warp_PtFcnDot        dot,         /**< Compute dot product of two temporal states*/
              warp_PtFcnBufSize    bufsize,     /**< Computes size for MPI buffer for one */
              warp_PtFcnBufPack    bufpack,     /**< Packs MPI buffer to contain one temporal state*/
              warp_PtFcnBufUnpack  bufunpack,   /**< Unpacks MPI buffer containing one temporal state*/
              warp_PtFcnCoarsen    coarsen,     /**< Spatially coarsen a vector. If null, test is skipped.*/
              warp_PtFcnRefine     refine       /**< Spatially refine a vector. If null, test is skipped.*/
              );

/** @}*/

#ifdef __cplusplus
}
#endif

#endif

