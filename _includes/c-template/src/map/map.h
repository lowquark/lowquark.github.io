#ifndef INCLUDE_GUARD_H
#define INCLUDE_GUARD_H

/* 
 * This is free and unencumbered software released into the public domain.
 * 
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 * 
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 * For more information, please refer to <http://unlicense.org>
 */

typedef unsigned long HASH_TYPEDEF;

typedef struct ENTRY_STRUCT ENTRY_TYPEDEF;


struct ENTRY_STRUCT {
  struct ENTRY_STRUCT * next;
  KEY_TYPEDEF   key;
  HASH_TYPEDEF  hash;
  VALUE_TYPEDEF value;
};

typedef struct MAP_STRUCT {
  ENTRY_TYPEDEF ** table;
  unsigned long table_size;
  unsigned long entry_count;
} MAP_TYPEDEF;


void MAP_METHOD(init)  (MAP_TYPEDEF * map);

void MAP_METHOD(clear) (MAP_TYPEDEF * map);


int  MAP_METHOD(get)   (MAP_TYPEDEF * map, KEY_TYPEDEF key, VALUE_TYPEDEF * value_out);

int  MAP_METHOD(set)   (MAP_TYPEDEF * map, KEY_TYPEDEF key, VALUE_TYPEDEF value);


int  MAP_METHOD(has)   (MAP_TYPEDEF * map, KEY_TYPEDEF key);

int  MAP_METHOD(erase) (MAP_TYPEDEF * map, KEY_TYPEDEF key);


#endif
