/* iaed25 - ist1114493 - project */

/**
 * @file main.c
 * @brief Vaccine Management System
 * 
 * This program implements a vaccine management system that allows for 
 * the management of vaccine batches, registration of users for vaccination and 
 * tracking of inoculations.
 * 
 * The program uses a hash table for quick lookup of inoculation records.
 * 
 * The system's operations depend on user input provided through a command-line 
 * interface, with commands starting with specific characters:
 * - 'c' for introducing a new batch.
 * - 'l' for listing vaccine batches.
 * - 'a' for applying a vaccine to a user.
 * - 'r' for disabling a batch.
 * - 'd' for deleting a vaccination record.
 * - 'u' for listing vaccination records.
 * - 't' for changing or displaying the system's date.
 * 
 * @author ist1114493 (Tomás Gomes)
 * @date 2025
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "errors.h"
#include "system.h"
#include "inoc.h"
#include "vaccine.h"
#include "hash.h"
#include "date.h"


#define BUFMAX      65535       /**< max. len. of input line    */


/** 
 * @brief Introduce a new vaccine batch into the system.
 * 
 * @param sys	system data
 * @param in	input line with batch details
 */
static void command_c(Sys *sys, char *in) {
    char batch[BUFMAX], name[BUFMAX];
    int doses;
    Date date;

    if (sys->nb == MAXBATCHES) {
        sys->is_pt ? puts(E2MANYVAC_PT): puts(E2MANYVAC_EN); return;
    }

    sscanf(in, "%*s %s %d-%d-%d %d %s", batch, &date.dd, &date.mm, &date.yy, 
        &doses, name);

    if (!verify_new_batch(sys->nb, batch, &sys->batches[0], sys->is_pt, name, 
        sys->date, date, doses)) return;

    // Allocate and store batch information and check for memory failure
    sys->batches[sys->nb].name = strdup(name);
    sys->batches[sys->nb].batch = strdup(batch);
    
    if (!sys->batches[sys->nb].name || !sys->batches[sys->nb].batch) 
        no_mem(sys);

    sys->batches[sys->nb].expdate = date;
    sys->batches[sys->nb].avdoses = doses;
    sys->batches[sys->nb].apdoses = 0;
    sys->nb++;

    printf("%s\n", batch);
}


/** 
 * @brief Lists the vaccine batches in the system, optionally filtered by 
 * vaccine name.
 *
 * @param sys	system data
 * @param in	input line with optional vaccine filter
 */
static void command_l(Sys *sys, char *in) {
    int i, batch_ex;
    char *vac_name;

    quicksort_batches(sys->batches, 0, sys->nb - 1);

    in += 2;

    /*if there is no vaccine filter - list all batches*/
    if (*in == '\n' || *in == '\0') {
        for (i = 0; i < sys->nb; i ++)
            print_l_vac(&sys->batches[i]);
        return;
    }

    /*if there is a vaccine filter - process each filter*/
    vac_name = strtok(in, " \t\n");
    while (vac_name) {
        batch_ex = 0;

        // Search for matching batches and print them
        for (i = 0; i < sys->nb; i++) {
            if (!strcmp(sys->batches[i].name, vac_name)) {
                batch_ex = 1;
                print_l_vac(&sys->batches[i]);
            }
        }

        if (!batch_ex) {
            printf("%s", vac_name);
            sys->is_pt ? puts(ENOVACINE_PT): puts(ENOVACINE_EN);
        }

        // Process the next vaccine name in the filter
        vac_name = strtok(NULL, " \t\n");
    }
}


/** 
 * @brief Applies a vaccine to a user, updating the system records.
 *
 * @param sys	system data
 * @param in	input line containing user and vaccine details
 */
static void command_a(Sys *sys, char *in) {
    char username[BUFMAX], vac_name[BUFMAX];
    Inoc *new_inocs;
    Vaccine *temp;
    
    if(sscanf(in, "%*s \"%[^\"]\" %s", username, vac_name) != 2) 
        sscanf(in, "%*s %s %s", username, vac_name);
           
    if (dup_inoc(username, vac_name, &sys->hash, sys->inocs, sys->date, 
        sys->is_pt)) return;

    // Reallocate memory for inoculations if necessary, checking for mem failure
    new_inocs = inoc_realloc(sys->ni, &sys->incocCap, sys->inocs);
    new_inocs ? sys->inocs = new_inocs : no_mem(sys);

    // Sorts and removes vac from system, checking for stock
    quicksort_batches(sys->batches, 0, sys->nb - 1);
    temp = aplly_bacth(sys->nb, &sys->batches[0], vac_name);
    
    if (!temp) { 
        sys->is_pt ? puts(ENOSTOCK_PT): puts(ENOSTOCK_EN); 
        return;
    }

    // Add the new inoculation to the system, checking for mem failure
    sys->inocs[sys->ni].user = strdup(username);
    if (!sys->inocs[sys->ni].user) no_mem(sys);
    
    sys->inocs[sys->ni].vaccine = temp;
    sys->inocs[sys->ni].apdate = sys->date;
    
    // Insert the inoculation record into the hash table
    hash_insert(&sys->hash, hash_get_key(username), sys->ni);

    sys->ni++;
}


/** 
 * @brief Disables a vaccine batch and removes it if unused.
 *
 * @param sys	system data
 * @param in	input line containing the batch ID to be disabled
 */
static void command_r(Sys *sys, char *in) {
    char batch[MAXBATCHNAME];
    int i, j, has_batch;

    sscanf(in, "%*s %s", batch);

    // Look for the batch in the system
    for (i = 0, has_batch = 0; i < sys->nb && !has_batch; i++) {
        
        // Check if the batch exists
        if (!strcmp(batch, sys->batches[i].batch)) {
            has_batch = 1;
            printf("%d\n", sys->batches[i].apdoses);

            // If the batch has doses applied, disable
            if (sys->batches[i].apdoses > 0)
                sys->batches[i].avdoses = 0;

            // Remove the batch completely if no doses are applied
            else { 
                free(sys->batches[i].batch);
                free(sys->batches[i].name);

                for (j = i; j < sys->nb; j++) {
                    sys->batches[j] = sys->batches[j+1];

                }
                sys->nb--;
            }
        }
    }

    if (!has_batch) {
        printf("%s", batch);
        sys->is_pt ? puts(ENOBATCH_PT): puts(ENOBATCH_EN);
    }
}


/** 
 * @brief Deletes a vaccination record for a user.
 *
 * @param sys	system data
 * @param in	input line with the user and optionally a date and batch 
 *              to delete the record
 */
static void command_d(Sys *sys, char *in) {
    int is_batch = 1, read_date = 0, read_batch = 0, val_date = 1, 
        narg, deletion;
    char username[BUFMAX], batch[MAXBATCHNAME];
    Date date;
    
    // Check for opptional paramethers and set according variables
    if (*(in+2) == '\"')
        narg = sscanf(in, "%*s \"%[^\"]\" %d-%d-%d %s", username, &date.dd, 
                        &date.mm, &date.yy, batch);
    else
        narg = sscanf(in, "%*s %s %d-%d-%d %s", username, &date.dd, &date.mm, 
                        &date.yy, batch);

    if (narg >= 4) {
        if (!is_date_valid(sys->date, date, 1)) val_date = 0;
        read_date = 1;

        if (narg == 5) {
            read_batch = 1;
            is_batch = 0;
        }
    }

    // Delete the inoculation record
    deletion = inoc_del(username, batch, &sys->hash, sys->inocs, read_date, 
                        read_batch, val_date, date, sys->ni, is_batch, 
                        sys->is_pt);
    
    // Stop if error found
    if (deletion == -1) return;

    // Update the total number of inoculations and show number of delitions
    sys->ni -= deletion;
    printf("%d\n", deletion);
}


/** 
 * @brief Lists inoculations for a specific user or all users.
 * 
 * @param sys	system data
 * @param in	input line with the optional username filter
 */
static void command_u(Sys *sys, char *in) {
    int i, is_user = 0;
    char username[BUFMAX];

    // Check if a username is provided
    if(sscanf(in, "%*s \"%[^\"]\"", username) != 1) {
        if (sscanf(in, "%*s %s", username) != 1) {

            // If no username, print all inoculations
            for (i = 0; i < sys->ni; i++)
                print_l_inoc(&sys->inocs[i]);
            return;
        }
    }    

    // Search for the inoculations of the given user
    for (i = 0; i < sys->ni; i++)
        if (!strcmp(username, sys->inocs[i].user)) {
            is_user = 1;
            print_l_inoc(&sys->inocs[i]);
        }
    
    if (!is_user) {
        printf("%s", username);
        sys->is_pt ? puts(EINVUSER_PT): puts(EINVUSER_EN);
    } 
}


/** 
 * @brief Sets or displays the current system date.
 *
 * @param sys	system data
 * @param in	input line with the optional date to set
 */
static void command_t(Sys *sys, char *in) {
    Date in_date;

    if (sscanf(in, "%*s %d-%d-%d", &in_date.dd, &in_date.mm, &in_date.yy)==3) {       
        if (!is_date_valid(sys->date, in_date, 0)) {
            sys->is_pt ? puts(EINVDATE_PT): puts(EINVDATE_EN);
            return;
        }
        sys->date = in_date;        // Update the system date if valid
    }

    // Print the current system date
    printf("%02d-%02d-%d\n", sys->date.dd, sys->date.mm, sys->date.yy);
}


/** 
 * @brief Main entry point of the program.
 * 
 * The function initializes the system, processes input commands and calls 
 * corresponding functions.
 * 
 * @param argc	number of command-line arguments
 * @param argv	array of command-line arguments
 * 
 * @return      0 if the program ends successfully
 */
int main(int argc, char *argv[]) {
    char buf[BUFMAX+1];
    Sys sys = sys_ini(argc, argv); // Initialize system
    
    // Loop to process input commands
    while (fgets(buf, BUFMAX+1, stdin))
		switch (buf[0]) {
			case 'q': free_mem(&sys); return 0;         // Free memory and exit
			case 'c': command_c(&sys, buf); break;      // Add a new batch
			case 'l': command_l(&sys, buf); break;      // List batches
			case 'a': command_a(&sys, buf); break;      // Apply a vaccine
			case 'r': command_r(&sys, buf); break;      // Disable a batch
			case 'd': command_d(&sys, buf); break;      // Delete inoculations
			case 'u': command_u(&sys, buf); break;      // List inoculations
			case 't': command_t(&sys, buf); break;      // Set or display date
		}
}