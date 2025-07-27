/**
 * @file vaccine.h
 * @brief Header file for vaccine-related functions in the vaccination system.
 * 
 * This header file defines the structure and functions related to managing 
 * vaccine batches in the vaccination system.
 * 
 * @author ist1114493 (Tomás Gomes)
 * @date 2025
 */

#ifndef _VACCINE_H_
#define _VACCINE_H_

#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "hash.h"
#include "date.h"

#define MAXVACNAMEB     50      /**< max. bytes of vaccine name */
#define MAXBATCHNAME    20      /**< max. len. of batch name    */


/**
 * @struct Vaccine
 * @brief Structure representing a vaccine batch.
 * 
 * This structure is used to store information about a specific vaccine batch.
 * It contains details about the vaccine's name, batch number, expiration date,
 * available doses, and applied doses.
 */
typedef struct {
    char *name;         /** Vaccine name. Dynamically allocated.    */
    char *batch;        /** Batch ID of the vaccine. Dynamically allocated. */
    Date expdate;       /** Expiration date of the vaccine batch.   */
    int avdoses;        /** The number of available doses in the batch. */
    int apdoses;        /** The number of doses applied from the batch. */
} Vaccine;


/**
 * @brief Checks if the vaccine batch name is valid.
 * 
 * @param batch The batch name to check.
 * 
 * @return 1 if valid, 0 if invalid.
 */
int is_batch_valid(char batch[]);


/**
 * @brief Checks if the vaccine name is valid.
 * 
 * @param name The vaccine name to check.
 * 
 * @return 1 if valid, 0 if invalid.
 */
int is_vacname_valid(char name[]);


/**
 * @brief Partitions the vaccine batches for quicksort.
 * 
 * This function is used in the quicksort algorithm to divide the batches into 
 * two groups: those with an expiration date earlier than the pivot and those 
 * with a later or equal expiration date. It also handles sorting by batch name 
 * when expiration dates are equal.
 * 
 * @param batches   The array of vaccine batches.
 * @param low       The starting index of the partition.
 * @param high      The ending index of the partition.
 * 
 * @return The partition index.
 */
int partition_batches(Vaccine batches[], int low, int high);


/**
 * @brief Sorts the vaccine batches using quicksort.
 * 
 * This function sorts an array of vaccine batches by expiration date, and 
 * if the expiration dates are the same, by batch name. 
 * 
 * @param batches   The array of vaccine batches.
 * @param low       The starting index for the quicksort.
 * @param high      The ending index for the quicksort.
 */
void quicksort_batches(Vaccine batches[], int low, int high);


/**
 * @brief Prints the details of a vaccine.
 * 
 * @param vac The vaccine to print.
 */
void print_l_vac(Vaccine *vac);


/**
 * @brief Verifies if a new vaccine batch can be added.
 * 
 * @param nb            The number of existing batches.
 * @param batch         The batch name to check.
 * @param batches       The array of existing vaccine batches.
 * @param is_pt         The language flag (1 for Portuguese, 0 for English).
 * @param name          The vaccine name to check.
 * @param current_date  The current date in the system.
 * @param date          The expiration date of the new batch.
 * @param doses         The number of doses in the batch.
 * 
 * @return 1 if valid, 0 if invalid.
 */
int verify_new_batch(int nb, char batch[], Vaccine *batches, int is_pt,
                    char name[], Date current_date, Date date, int doses);


/**
 * @brief Applies a vaccine batch to a user.
 * 
 * This function decreases the available doses of a vaccine batch and increases 
 * the applied doses when a batch is successfully applied to a user.
 * 
 * @param nb        The number of vaccine batches in the system.
 * @param batches   The array of vaccine batches.
 * @param vac_name  The name of the vaccine batch to apply.
 * 
 * @return A pointer to the applied vaccine batch, or NULL if not found.
 */
Vaccine * aplly_bacth(int nb, Vaccine *batches, char vac_name[]);

#endif