/**
 * @file inoc.h
 * @brief Header file for Inoculation operations.
 * 
 * This file defines the structures and functions used for managing the 
 * inoculation records in the vaccine management system.
 * 
 * The structure `Inoc` holds the user, vaccine, and application date 
 * information for each inoculation.
 */

#ifndef _INOC_H_
#define _INOC_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "vaccine.h"
#include "date.h"

#define INOCMEM         100     /**< Initial memory for inoculations. */


/**
 * @brief Structure for an Inoculation record.
 * 
 * This structure holds the information related to a single inoculation record,
 * which includes the user's details, the vaccine used, and the application 
 * date.
 */
typedef struct {
    char *user;             /**< Username of the person who got vaccinated. */
    Vaccine *vaccine;       /**< Pointer to the vaccine used for inoculation. */
    Date apdate;            /**< Date the vaccination was applied. */
} Inoc;

/**
 * @brief Checks for a duplicate inoculation for a given user and vaccine.
 * 
 * @param username          The username of the user to check.
 * @param vac_name          The vaccine name to check.
 * @param hash              The hash table used for quick lookup.
 * @param inocs             The array of inoculations.
 * @param current_date      The current date to check against.
 * @param is_pt             The language flag (1 for Portuguese, 0 for English).
 * 
 * @return  1 if a duplicate is found, 0 otherwise.
 */
int dup_inoc(char username[], char vac_name[], Hash *hash, Inoc *inocs, 
                Date current_date, int is_pt);


/**
 * @brief Reallocates memory for the inoculations array if needed.
 * 
 * @param ni         The current number of inoculations.
 * @param incocCap   The current capacity of the inoculations array.
 * @param inocs      The array of inoculations.
 * 
 * @return  The reallocated inoculations array / NULL if error.
 */
Inoc *inoc_realloc(int ni, int *incocCap, Inoc *inocs);


/**
 * @brief Prints the details of an inoculation record.
 * 
 * @param inoc  The inoculation record to print.
 */
void print_l_inoc(Inoc *inoc);


/**
 * @brief Removes an inoculation record from the hash table.
 * 
 * @param hash       The hash table storing inoculation records.
 * @param username   The username of the inoculation that is to be removed.
 * @param inocs      The array of inoculations.
 * @param read_date  Flag indicating if date filtering is enabled.
 * @param read_batch Flag indicating if batch filtering is enabled.
 * @param batch      The batch number to filter by.
 * @param date       The date to filter by.
 */
void inoc_hash_remove(Hash *hash, char username[], Inoc *inocs, int read_date, 
                        int read_batch, char batch[], Date date);


/**
 * @brief Removes an inoculation record from the inoculations array.
 * 
 * @param ni         The current number of inoculations.
 * @param inocs      The array of inoculations.
 * @param username   The username of the inoculation that is to be removed.
 * @param read_date  Flag indicating if date filtering is enabled.
 * @param read_batch Flag indicating if batch filtering is enabled.
 * @param is_batch   Flag indicating if the batch filter is applied.
 * @param date       The date to filter by.
 * @param batch      The batch number to filter by.
 * 
 * @return The number of records removed or error code.
 */
int inoc_remove(int ni, Inoc *inocs, char username[], int read_date,
                int read_batch, int is_batch, Date date, char batch[]);


/**
 * @brief Deletes an inoculation record based on specific criteria.
 * 
 * @param username      The username of the inoculation that is to be removed.
 * @param batch         The batch number to filter by.
 * @param hash          The hash table storing inoculation records.
 * @param inocs         The array of inoculations.
 * @param read_date     Flag indicating if date filtering is enabled.
 * @param read_batch    Flag indicating if batch filtering is enabled.
 * @param val_date      Flag indicating if date is valid.
 * @param date          The date to filter by.
 * @param ni            The current number of inoculations.
 * @param is_batch      Flag indicating if the batch filter is applied.
 * @param is_pt         The language flag
 * 
 * @return The number of records removed or an error code.
 */
int inoc_del(char username[], char batch[], Hash *hash, Inoc *inocs, 
            int read_date, int read_batch, int val_date, Date date, int ni, 
            int is_batch, int is_pt);

#endif