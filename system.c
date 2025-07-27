/**
 * @file system.c
 * @brief System management functions for the Vaccine Management System.
 * 
 * This file contains functions responsible for initializing, freeing memory, 
 * and handling memory allocation failures in the Vaccine Management System.
 * 
 * @author ist1114493 (Tomás Gomes)
 * @date 2025
 */

#include "system.h"


Sys sys_ini(int argc, char *argv[]) {
    Sys sys;

    // Set inicial values
    sys.nb = sys.ni = 0;
    sys.incocCap = INOCMEM;
    sys.date.dd = INIDD;
    sys.date.mm = INIMM;
    sys.date.yy = INIYY;

    // Allocate the initial memory for the inoculations array
    sys.inocs = (Inoc *) malloc(INOCMEM * sizeof(Inoc));

    // Initialize the hash table for quick lookups
    sys.hash = hash_ini();

    // Check if the second command-line argument is "pt" -> Portuguese language
    sys.is_pt = (argc == 2 && !strcmp(argv[1], "pt")) ? 1 : 0;

    return sys;
}


void free_mem(Sys *sys) {
    int i;
    
    // Free batches memory
    for (i = 0; i < sys->nb; i++) {
        free(sys->batches[i].name);
        free(sys->batches[i].batch);
    }

    // Free hash memory
    hash_free(&sys->hash);

    // Free inoculations memory
    for (i = 0; i < sys->ni; i++) free(sys->inocs[i].user); 
    free(sys->inocs);
}


void no_mem(Sys *sys) {

    free_mem(sys);
    sys->is_pt ? puts(ENOMEMORY_PT): puts(ENOMEMORY_EN);
    exit(EXIT_SUCCESS);
}