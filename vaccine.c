/**
 * @file vaccine.c
 * @brief Functions for managing vaccine batches.
 * 
 * This file contains functions for managing vaccine batches, including 
 * validation, sorting, and applying vaccines to users.
 * 
 * @author ist1114493 (Tomás Gomes)
 * @date 2025
 */

#include "vaccine.h"


int is_batch_valid(char batch[]) {
    int i;

    if (strlen(batch) > MAXBATCHNAME) return 0;

    // Validate each character in the batch name
    for (i = 0; batch[i] != '\0'; i++)      
        if (!(('A' <= batch[i] && batch[i] <= 'F') || 
            ('0' <= batch[i] && batch[i] <= '9')))
            return 0;
    
    return 1;
}


int is_vacname_valid(char name[]) {
    int i;

    if (strlen(name) > MAXVACNAMEB) return 0;

    // Validate each character in the vaccine name
    for (i = 0; name[i] != '\0'; i++)       
        if (name[i] == ' ' || name[i] == '\n' || name[i] == '\t') return 0;

    return 1;
}


int partition_batches(Vaccine batches[], int low, int high) {
    Vaccine pivot = batches[high], aux;
    int i = low - 1, j, cmp;

    for (j = low; j < high; j++) {

        // Compare expiration dates  / Sort by batch name if dates are equal
        cmp = compare_dates(batches[j].expdate, pivot.expdate);     
        if (cmp == 1 || (cmp == 0 && 
            strcmp(batches[j].batch, pivot.batch) < 0)) {

            i++;
            aux = batches[i];
            batches[i] = batches[j];
            batches[j] = aux;
        }
    }

    aux = batches[i + 1];
    batches[i + 1] = batches[high];
    batches[high] = aux;
    
    return i + 1;
}


void quicksort_batches(Vaccine batches[], int low, int high) {
    int i;

    if (low >= high) return;

    i = partition_batches(batches, low, high);  // Partition the array
    quicksort_batches(batches, low, i-1);   // Recursively sort the left part 
    quicksort_batches(batches, i+1, high);  // Recursively sort the right part
}


void print_l_vac(Vaccine *vac) {
    
    printf("%s %s %02d-%02d-%d %d %d\n", vac->name, vac->batch, vac->expdate.dd, 
            vac->expdate.mm, vac->expdate.yy, vac->avdoses, vac->apdoses);
}


int verify_new_batch(int nb, char batch[], Vaccine *batches, int is_pt,
                    char name[], Date current_date, Date date, int doses) {
    int i;

    //find if batch already exists
    for (i = 0; i < nb; i++)
        if (!strcmp(batch, batches[i].batch)) {
            is_pt ? puts(EDUPBATCH_PT): puts(EDUPBATCH_EN);
            return 0;
        }

    // Check other errors
    if (!is_batch_valid(batch)) {
        is_pt ? puts(EINVBATCH_PT): puts(EINVBATCH_EN);
        return 0;
    }

    if (!is_vacname_valid(name)) {
        is_pt ? puts(EINVNAME_PT): puts(EINVNAME_EN);
        return 0;
    }

    if (!is_date_valid(current_date, date, 0)) {
        is_pt ? puts(EINVDATE_PT): puts(EINVDATE_EN);
        return 0;
    }

    if (doses <= 0) {
        is_pt ? puts(EINVQUANT_PT): puts(EINVQUANT_EN);
        return 0;
    }

    return 1;
}

Vaccine * aplly_bacth(int nb, Vaccine *batches, char vac_name[]) {
    int i, batch_found;


    for (i = 0, batch_found = 0; i < nb && !batch_found; i++) {
        
        // Check if vaccine is available
        if (!strcmp(batches[i].name, vac_name) && 
            batches[i].avdoses > 0) {

            batch_found = 1;
            batches[i].avdoses -= 1;
            batches[i].apdoses += 1;
            puts(batches[i].batch);

            return &batches[i];
        }
    }

    return NULL;        // Return NULL if batch is not found or not available
}