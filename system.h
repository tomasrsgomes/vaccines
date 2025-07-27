/**
 * @file system.h
 * @brief Vaccine Management System - System Structure and Initialization
 * 
 * This file contains the definitions for the main system structure and related
 * functions in the Vaccine Management System. The `Sys` structure represents 
 * the system, including the vaccine batches, inoculation records, and the 
 * current system date. It also manages the system's hash table and memory 
 * handling.
 * 
 * @author ist1114493 (Tomás Gomes)
 * @date 2025
 */

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <stdlib.h>
#include <string.h>

#include "vaccine.h"
#include "inoc.h"
#include "date.h"

#define MAXBATCHES      1000        /**< max. num. of batches   */
#define INIDD           1           /** Initial day for system date */
#define INIMM           1           /** Initial month for system date   */
#define INIYY           2025        /** Initial year for system date    */


/**
 * @struct Sys
 * @brief Represents the state of the Vaccine Management System.
 * 
 * This structure holds all the information necessary to manage the system.
 */
typedef struct {
    int nb;     /**< Number of vaccine batches in the system */
    Vaccine batches[MAXBATCHES];        /**< Array of vaccine batches */

    int ni, incocCap;       /**< Number of inocs and inoc capacity */
    Inoc *inocs;        /**< Pointer to an array of inoculation records */

    Hash hash;      /**< Hash table for quick lookup of inoculation records */

    Date date;      /**< Current system date */
    int is_pt;      /**< Language flag (1 for Portuguese, 0 for English) */
} Sys;


/**
 * @brief Initializes the system with default values.
 * 
 * @param argc  Number of command-line arguments.
 * @param argv  Array of command-line arguments.
 * 
 * @return      A fully initialized `Sys` structure.
 */
Sys sys_ini(int argc, char *argv[]);


/**
 * @brief Frees all dynamically allocated memory used by the system.
 * 
 * @param sys Pointer to the system structure.
 */
void free_mem(Sys *sys);


/**
 * @brief Handles memory allocation failures.
 * 
 * @param sys Pointer to the system structure.
 */
void no_mem(Sys *sys);

#endif