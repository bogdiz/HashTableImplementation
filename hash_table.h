#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct{
    char* key;
    char* value;
}ht_item;

typedef struct{
    int size;
    int base_size;
    int count;
    ht_item** items;
}ht_hash_table;

static ht_item* ht_new_item(const char* , const char* );
ht_hash_table* ht_new();
static void ht_del_item (ht_item* );
void ht_del_hash_table (ht_hash_table* );

static int ht_hash(const char* , const int , const int );
static int ht_get_hash(const char*, const int, const int );

void ht_insert(ht_hash_table* ht, const char* , const char* );
char* ht_search(ht_hash_table* ht, const char* );
void ht_delete(ht_hash_table* h, const char* );

static ht_hash_table* ht_new_sized(const int ); 
static void ht_resize(ht_hash_table* , const int );
static void ht_resize_up(ht_hash_table* );
static void ht_resize_down(ht_hash_table* );


#endif