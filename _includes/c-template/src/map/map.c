
#include "map.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

static const unsigned long initial_size = 32;

map_hash_t map_hash(map_key_t key) {
  /* TODO: Implement hash */
  return key;
}

static int key_eq(map_key_t key0, map_key_t key1) {
  return memcmp(&key0, &key1, sizeof(map_key_t)) == 0;
}

static unsigned long hash_idx(map_key_t key, unsigned long table_size) {
  assert(table_size > 0);

  return map_hash(key) % table_size;
}

static map_entry_t ** bucket_of(map_t * h, map_key_t key) {
  assert(h->table);

  return h->table + hash_idx(key, h->table_size);
}

static int resize_table(map_t * h, unsigned long newsize) {
  unsigned long i;
  unsigned long table_size = h->table_size;
  map_entry_t ** table = h->table;
  map_entry_t ** newtable = calloc(sizeof(*newtable), newsize);

  if(!newtable) {
    return 0;
  }

  for(i = 0 ; i < table_size ; i ++) {
    /* free chain */
    map_entry_t * entry = table[i];

    while(entry) {
      /* save next pointer */
      map_entry_t * next = entry->next;

      unsigned long idx = hash_idx(entry->key, newsize);

      /* lookup chain in the new table */
      map_entry_t ** slot = newtable + idx;

      /* advance slot in the new chain */
      while(*slot) {
        assert(!key_eq((*slot)->key, entry->key));
        slot = &(*slot)->next;
      }

      /* place at end of destination chain */
      *slot = entry;
      entry->next = NULL;

      /* repeate again with the next entry in the old chain */
      entry = next;
    }
  }

  free(table);
  h->table = newtable;
  h->table_size = newsize;

  return 1;
}

void map_init(map_t * m) {
  m->table       = NULL;
  m->table_size  = 0;
  m->entry_count = 0;
}
void map_clear(map_t * h) {
  unsigned long i;
  unsigned long table_size = h->table_size;
  map_entry_t ** table = h->table;

  for(i = 0 ; i < table_size ; i ++) {
    /* free chain */
    map_entry_t * entry = table[i];

    while(entry) {
      /* cache next pointer */
      map_entry_t * next = entry->next;
      /* free this one */
      /* deinit(entry->value); */
      free(entry);
      /* try again with the next */
      entry = next;
    }

    table[i] = NULL;
  }

  /* free buffer */
  free(h->table);

  /* cleared! */
  h->table = NULL;
  h->table_size = 0;
}

int map_get(map_t * h, map_key_t key, map_value_t * value_out) {
  map_entry_t * list;

  if(h->table == NULL) { return 0; }

  list = *bucket_of(h, key);

  while(list) {
    if(key_eq(list->key, key)) {
      *value_out = list->value;
      return 1;
    }
    list = list->next;
  }

  return 0;
}
int map_erase(map_t * h, map_key_t key) {
  if(h->table == NULL) { return 0; }

  map_entry_t ** slot = bucket_of(h, key);

  while(*slot) {
    map_entry_t * entry = *slot;

    if(key_eq(entry->key, key)) {
      /* matches, skip over */
      *slot = entry->next;
      /* free */
      /* deinit(entry->value); */
      free(entry);

      h->entry_count --;

      return 1;
    }

    slot = &entry->next;
  }

  return 0;
}
int map_set(map_t * h, map_key_t key, map_value_t value) {
  assert(h);

  if(h->table == NULL) { 
    /* initialize if not already */
    h->table = calloc(sizeof(map_entry_t *), initial_size);

    /* couldn't alloc, escape before anything breaks */
    if(!h->table) { return 0; }

    h->table_size = initial_size;
  }

  if(h->entry_count > h->table_size*2) {
    if(!resize_table(h, h->table_size * 2)) {
      /* couldn't resize, escape before anything breaks */
      return 0;
    }
  }

  map_entry_t ** slot = bucket_of(h, key);

  /* advance last slot */
  while(*slot) {
    map_entry_t * entry = *slot;

    if(key_eq(entry->key, key)) {
      /* already exists, overwrite */
      /* deinit(entry->value); */
      entry->value = value;
      return 1;
    }

    slot = &(*slot)->next;
  }

  /* reached end of chain, create a new entry */
  map_entry_t * new_entry = malloc(sizeof(*new_entry));

  /* couldn't alloc, escape before anything breaks */
  if(!new_entry) { return 0; }

  new_entry->next = NULL;
  new_entry->key = key;
  new_entry->value = value;
  *slot = new_entry;

  h->entry_count ++;

  return 1;
}

