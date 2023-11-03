#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash_table.h"
#include "prime.h"

static const int HT_PRIME_1 = 151;
static const int HT_PRIME_2 = 163;
static ht_item HT_DELETED_ITEM = {NULL, NULL};
static const int HT_INITIAL_BASE_SIZE = 53; 


static ht_item* ht_new_item(const char* k, const char* val){
    ht_item* i = malloc(sizeof(ht_item));
    i->key = strdup(k);
    i->value = strdup(val);
    return i;
}

ht_hash_table* ht_new(){
    // ht_hash_table* ht = malloc(sizeof(ht_hash_table));

    // ht->size = 53;
    // ht->count = 0;
    // ht->items = calloc((size_t)ht->size, sizeof(ht_item*));

    return ht_new_sized(HT_INITIAL_BASE_SIZE);
}

static void ht_del_item (ht_item* i){
    free(i->key);
    free(i->value);
    free(i);
}

void ht_del_hash_table (ht_hash_table* ht){
    for (int j = 0; j < ht->size; ++j){
        ht_item* i = ht->items[j];
        if (i != NULL)
            ht_del_item(i);
    }
    free(ht->items);
    free(ht);
}

//hash function
static int ht_hash (const char* s, const int a, const int size){
    long int hash = 0;
    for (int i = 0; i < strlen(s); ++i){
        hash += (long)pow(a, strlen(s) - (i + 1)) * s[i];
        hash %= size;
    }

    return (int)hash;
}

//double hashing in case of collisions
static int ht_get_hash (const char* s, const int nr_buckets, const int attempt){
    const int hash_a = ht_hash(s, HT_PRIME_1, nr_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, nr_buckets);

    //in case of no collision, we will return just hash_a, attempt being 0
    return (hash_a + (attempt * (hash_b + 1))) % nr_buckets;
}

void ht_insert(ht_hash_table* ht, const char* key, const char* value){
    const int load = ht->count * 100 / ht->size;
    //if the load i too high, resize it up
    if (load > 70)
        ht_resize_up(ht);

    ht_item* item = ht_new_item(key, value);

    int index = ht_get_hash(item->key, ht->size, 0);
    //item cur_item we will search with 
    ht_item* cur_item = ht->items[index];
    int i = 1;
    //search until we find a non-occupied item in ht->items
    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM){
        //update in case we insert item with the same key
        if (strcmp(cur_item->key, key) == 0){
            ht_del_item(cur_item);
            ht->items[index] = item;
        }
        index = ht_get_hash(item->key, ht->size, i);
        cur_item = ht->items[index];
        ++i;
    }

    ht->items[index] = item;
    ++ht->count;
}

char* ht_search(ht_hash_table* ht, const char* key){
    int index = ht_get_hash(key, ht->size, 0); 
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL){
        if (strcmp(item->key, key) == 0 && item != &HT_DELETED_ITEM)
            return item->value;
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        ++i;
    }    

    return NULL;
}


void ht_delete(ht_hash_table* ht, const char* key){
        const int load = ht->count * 100 / ht->size;
    
        // if the load is too low (but not lower than minimum load = HT_INITIAL_BASE_SIZE), resize it down
        if (load < 10)
            ht_resize_down(ht);

        int index = ht_get_hash(key, ht->size, 0);
        ht_item* item = ht->items[index];
        int i = 1;

        while (item != NULL){
            if (item != &HT_DELETED_ITEM)
                if (strcmp(item->key, key) == 0){
                    ht_del_item(item);
                    //the item we wish to delete may be part of a collision chain, so we only mark it with HT_DELETED_ITEM
                    ht->items[index] = &HT_DELETED_ITEM;
                }
            index = ht_get_hash(key, ht->size, i);
            item = ht->items[index];
            ++i;
        }
        --ht->count;
}

static ht_hash_table* ht_new_sized(const int base_size){
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));
    ht->base_size = base_size;

    //we can change the size with the prime number greater or equal than base size
    ht->size = next_prime(base_size);

    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    
    return ht;
}

static void ht_resize(ht_hash_table* ht, const int base_size){
    //can't go lower than HT_INITIAL_BASE_SIZE
    if (base_size < HT_INITIAL_BASE_SIZE)
        return;

    //create a new hash table with new size (greater or lower)
    ht_hash_table* new_ht = ht_new_sized(base_size);
    //insert into new hash table all the items
    for (int i = 0; i < ht->size; ++i){
        ht_item* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM)
            ht_insert(new_ht, item->key, item->value);
    }

    //copy base_size, count, size from new_ht to ht
    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;
    ht->size = new_ht->size;

    //swap new_ht with ht to delete new_ht later without memory leaks 
    ht_item** aux2 = ht->items;
    ht->items = new_ht->items;
    new_ht->items = aux2;

    ht_del_hash_table(new_ht);

}

static void ht_resize_up(ht_hash_table* ht){
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}

static void ht_resize_down(ht_hash_table* ht){
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}



