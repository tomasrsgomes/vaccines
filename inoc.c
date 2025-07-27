/**
 * @file inoc.c
 * @brief Functions for managing inoculation records in the vaccination system.
 * 
 * This file ensures proper management of inoculation data.
 * 
 * @author ist114493 (Tomás Gomes)
 * @date 2025
 */

#include "inoc.h"

int dup_inoc(char username[], char vac_name[], Hash *hash, Inoc *inocs, 
            Date current_date, int is_pt) {
    int i, key;
    Inoc inoc;

    key = hash_get_key(username);       // Get hash key for the username.
    for(i = 0; i < hash->niIdx[key]; i++) {
        inoc = inocs[hash->inocsIdx[key][i]];       // Access inoc record.

        // Check if the same user, vaccine, and date exist in the records.
        if (!strcmp(username, inoc.user) && 
            !compare_dates(current_date, inoc.apdate) && 
            !strcmp(vac_name, inoc.vaccine->name)) {
            
            is_pt ? puts(EDOUBLEVAC_PT): puts(EDOUBLEVAC_EN);
            return 1;
        }
    }
    return 0;
}

Inoc *inoc_realloc(int ni, int *incocCap, Inoc *inocs) {
    Inoc *new_inocs;

    if (ni == *incocCap) {      // Check if the capacity is full.
        new_inocs = (Inoc*) realloc(inocs, (*incocCap+INOCMEM) * sizeof(Inoc));
        *incocCap += INOCMEM;

        if (!new_inocs) return NULL;        // Memory allocation fail

        inocs = new_inocs;
    }

    return inocs;
}


void print_l_inoc(Inoc *inoc) {
    
    printf("%s %s %02d-%02d-%d\n", inoc->user, inoc->vaccine->batch, 
            inoc->apdate.dd, inoc->apdate.mm, inoc->apdate.yy);
}


void inoc_hash_remove(Hash *hash, char username[], Inoc *inocs, int read_date, 
                        int read_batch, char batch[], Date date) {
    int i, j, key = hash_get_key(username);
    Inoc *inoc;

    // Loop through the hash table to find the matching inoculation record.
    for (i = 0; i < hash->niIdx[key]; i++) {
        
        inoc = &inocs[hash->inocsIdx[key][i]];
        if (!strcmp(username, inoc->user)) {
            
            if ((!read_date && !read_batch) ||
                (!read_batch && !compare_dates(date, inoc->apdate)) ||
                (!compare_dates(date, inoc->apdate) && 
                !strcmp(batch, inoc->vaccine->batch))) {
                
                // Shift remaining records to remove the current one.
                for (j = i; j < hash->niIdx[key] - 1; j++)
                    hash->inocsIdx[key][j] = --hash->inocsIdx[key][j+1];
            
                hash->niIdx[key]--;
                i--;        // Adjust index due to shifted records.
            }
        }
    }
}


int inoc_remove(int ni, Inoc *inocs, char username[], int read_date,
                int read_batch, int is_batch, Date date, char batch[]) {
    int i, j, del_count = 0, is_user = 0;
    Inoc *inoc;
    
    // Loop through the inoculations to find matching records.
    for (i = 0; i < ni; i++) {
        
        inoc = &inocs[i];
        if (!strcmp(username, inoc->user)) {
        
            if ((!read_date && !read_batch) ||
                (!read_batch && !compare_dates(date, inoc->apdate)) ||
                (!compare_dates(date, inoc->apdate) && 
                !strcmp(batch, inoc->vaccine->batch))) {

                free(inoc->user);

                // Shift remaining records to remove the current one.
                for (j = i; j < ni - 1; j++) inocs[j] = inocs[j+1];

                ni--;
                del_count++;
                is_batch = 1;
                i--;        // Adjust index due to shifted records.
            }
            is_user = 1;
        }
    }

    if (!is_user) return -1;
    if (!is_batch) return -2;
    return del_count;
}

int inoc_del(char username[], char batch[], Hash *hash, Inoc *inocs, 
            int read_date, int read_batch, int val_date, Date date, int ni, 
            int is_batch, int is_pt) {
    int removed;

    // Remove the inoculation record from the hash table.
    if (val_date)
        inoc_hash_remove(hash, username, inocs, read_date, read_batch, 
                        batch, date);

    // Remove the inoculation record from the inoculations array.
    removed = inoc_remove(ni, inocs, username, read_date, read_batch, 
                            is_batch, date, batch);

    // Error handle
    if (removed == -1) {
        printf("%s", username);
        is_pt ? puts(EINVUSER_PT): puts(EINVUSER_EN);
        return -1;
    }

    if (!val_date) { is_pt ? puts(EINVDATE_PT): puts(EINVDATE_EN); return -1; }

    if (removed == -2) {
        printf("%s", batch);
        is_pt ? puts(ENOBATCH_PT): puts(ENOBATCH_EN);        
        return -1;
    }

    return removed;
}