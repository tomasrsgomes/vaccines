/**
 * @file hash.c
 * @brief Hash table implementation for inoculation indexing.
 * 
 * This file provides the implementation of a simple hash table used to 
 * index and quickly access inoculation records associated with users.
 * The table uses the first character of the username as the hash key.
 * 
 * @author ist1114493 (Tomás Gomes)
 * @date 2025
 */

#include "hash.h"

Hash hash_ini() {
    Hash hash;
    int i;

    for (i = 0; i < MAXHASHKEY; i++) {
        hash.niIdx[i] = 0;
        hash.inocCapIdx[i] = HASHMEM;
        hash.inocsIdx[i] = (int*) malloc(HASHMEM * sizeof(int*));
    }

    return hash;

}


void hash_free(Hash *hash) {
    int i;

    for(i = 0; i < MAXHASHKEY; i++)
        free(hash->inocsIdx[i]);
}


int hash_get_key(char *str) {
    return str[0];
}


void hash_insert(Hash *hash, int key, int ni) {

    // Resize if the current capacity is full
    if (hash->niIdx[key] == hash->inocCapIdx[key]){

        hash->inocsIdx[key] = (int*) realloc(hash->inocsIdx[key], 
                            (hash->inocCapIdx[key] + HASHMEM) * sizeof(int*));
        
        hash->inocCapIdx[key] += HASHMEM;
    }

    // Store the new inoculation index in the hash bucket
    hash->inocsIdx[key][hash->niIdx[key]++] = ni;
}