#ifndef MAP_H
#define MAP_H

typedef unsigned long map_hash_t;
typedef int           map_key_t;
typedef int           map_value_t;

map_hash_t map_hash(map_key_t key);

typedef struct map_entry {
  struct map_entry * next;
  map_key_t   key;
  map_hash_t  hash;
  map_value_t value;
} map_entry_t;

typedef struct {
  map_entry_t ** table;
  unsigned long table_size;
  unsigned long entry_count;
} map_t;

void map_init(map_t * m);
void map_clear(map_t * m);

int map_get(map_t * m, map_key_t key, map_value_t * value_out);

int map_erase(map_t * m, map_key_t key);

int map_set(map_t * m, map_key_t key, map_value_t value);

#endif
