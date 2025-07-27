/**
 * @file hash.h
 * @brief Hash table interface for indexing inoculation records.
 * 
 * This header defines the structure and function prototypes for a simple 
 * hash table used to index and retrieve vaccination records efficiently.
 * 
 * @author ist1114493 (Tomás Gomes)
 * @date 2025
 */

#ifndef _HASH_H_
#define _HASH_H_

#include <stdlib.h>

#define MAXHASHKEY      256     /** Maximum number of hash keys (buckets)   */
#define HASHMEM         100     /** Initial memory per bucket   */


/**
 * @struct Hash
 * @brief Hash table structure for indexing inoculation records.
 * 
 * The hash table is used for quick access to a user's vaccination history
 * in the vaccine management system.
 */
typedef struct {
    int niIdx[MAXHASHKEY];      /**< Number of inoculations for each key. */
    int inocCapIdx[MAXHASHKEY];     /**< Current capacity for each key. */

    /**< Dynamic array holding the inoculation indices for each key. */
    int *inocsIdx[MAXHASHKEY];
} Hash;


/**
 * @brief Initializes a Hash structure.
 * 
 * Allocates memory for each entry in the hash table and sets initial sizes.
 * 
 * @return Initialized Hash structure.
 */
Hash hash_ini();


/**
 * @brief Frees the memory used by the hash table.
 * 
 * @param hash Pointer to the Hash structure to be freed.
 */
void hash_free(Hash *hash);


/**
 * @brief Gets the hash key for a username.
 * 
 * @param str   Username string.
 * 
 * @return      Hash key.
 */
int hash_get_key(char *str);


/**
 * @brief Inserts a new inoculation index into the hash table.
 * 
 * Dynamically resizes the storage if necessary.
 * 
 * @param hash  Pointer to the Hash table.
 * @param key   Hash key corresponding to the user.
 * @param ni    Index of the inoculation record.
 */
void hash_insert(Hash *hash, int key, int ni);

#endif
