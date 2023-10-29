#include <stdio.h>

#include "hash_table.h"
#include "prime.h"

int main(){
    ht_hash_table* ht = ht_new();
    ht_insert(ht, "cat", "vietnamese");
    ht_insert(ht, "cat1", "vietnamese1");
    ht_insert(ht, "cat2", "vietnamese");
    ht_insert(ht, "cat3", "vietnamese");
    ht_insert(ht, "cat4", "vietnamese");
    ht_insert(ht, "cat5", "vietnamese");
    ht_insert(ht, "cat6", "vietnamese");
    ht_insert(ht, "cat7", "vietnamese");
    ht_insert(ht, "cat8", "vietnamese");
    ht_insert(ht, "cat9", "vietnamese");
    ht_insert(ht, "cata", "vietnamese");
    ht_insert(ht, "catb", "vietnamese");
    ht_insert(ht, "catc", "vietnamese");
    ht_insert(ht, "catd", "vietnamese");
    ht_insert(ht, "cate", "vietnamese");
    ht_insert(ht, "catf", "vietnamese");
    ht_insert(ht, "catg", "vietnamese");
    ht_insert(ht, "cath", "vietnamese");
    ht_insert(ht, "catj", "vietnamese");
    ht_insert(ht, "catk", "vietnamese");
    ht_insert(ht, "catl", "vietnamese");
    ht_insert(ht, "catz", "vietnamese");
    ht_insert(ht, "catx", "vietnamese");
    ht_insert(ht, "catc", "vietnamese");
    ht_insert(ht, "catv", "vietnamese");
    ht_insert(ht, "catb", "vietnamese");
    ht_insert(ht, "catn", "vietnamese");
    ht_insert(ht, "catm", "vietnamese");
    ht_insert(ht, "cat,", "vietnamese");
    ht_insert(ht, "catq", "vietnamese");
    ht_insert(ht, "ca", "vietnamese");
    ht_insert(ht, "catt", "vietnamese");
    ht_insert(ht, "catȚ", "vietnamese");
    ht_insert(ht, "cat`", "vietnamese");
    ht_insert(ht, "cat~", "vietnamese");
    ht_insert(ht, "catoO", "vietnamese");
    ht_insert(ht, "cat0", "vietnamese");
    ht_insert(ht, "cat33", "vietnamese");
    ht_insert(ht, "cat41", "vietnamese");
    ht_insert(ht, "cat21", "vietnamese");
    ht_insert(ht, "cat445", "vietnamese");
    ht_insert(ht, "cat1112", "vietnamese");
    printf("%d", ht->size);

}