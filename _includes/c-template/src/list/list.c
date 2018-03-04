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

#include "FILENAME.h"

#include <stddef.h>
#include <stdlib.h>

void LIST_METHOD(init)(LIST_TYPEDEF * l) {
  l->next = l;
  l->prev = l;
  l->head = l;
}

void LIST_METHOD(clear)(LIST_TYPEDEF * l) {
  LIST_TYPEDEF * l_iter;
  LIST_TYPEDEF * l_iter_next;
  NODE_TYPEDEF * node;

  l_iter = l->next;

  while(l_iter != l) {
    l_iter_next = l_iter->next;

    /* no offsetof *should* be necessary */
    node = (NODE_TYPEDEF *)l_iter;

    /* deinit(&node->value) */
    free(node);

    l_iter = l_iter_next;
  }

  LIST_METHOD(init)(l);
}

void LIST_METHOD(erase)(NODE_TYPEDEF * node) {
  node->list.prev->next = node->list.next;
  node->list.next->prev = node->list.prev;

  node->list.next = &node->list;
  node->list.prev = &node->list;
  node->list.head = &node->list;

  /* deinit(&node->value) */

  free(node);
}

NODE_TYPEDEF * LIST_METHOD(push,back)(LIST_TYPEDEF * l, VALUE_TYPEDEF value) {
  NODE_TYPEDEF * newnode = calloc(sizeof(NODE_TYPEDEF), 1);

  if(newnode) {
    newnode->list.next       = l;
    newnode->list.prev       = l->prev;
    l->prev                  = &newnode->list;
    newnode->list.prev->next = &newnode->list;
    newnode->list.head       = l->head;
    newnode->value = value;
  }

  return newnode;
}

NODE_TYPEDEF * LIST_METHOD(push,front)(LIST_TYPEDEF * l, VALUE_TYPEDEF value) {
  NODE_TYPEDEF * newnode = calloc(sizeof(NODE_TYPEDEF), 1);

  if(newnode) {
    newnode->list.prev       = l;
    newnode->list.next       = l->next;
    l->next                  = &newnode->list;
    newnode->list.next->prev = &newnode->list;
    newnode->list.head       = l->head;
    newnode->value = value;
  }

  return newnode;
}

NODE_TYPEDEF * LIST_METHOD(insert,before)(NODE_TYPEDEF * node, VALUE_TYPEDEF value) {
  NODE_TYPEDEF * newnode = calloc(sizeof(NODE_TYPEDEF), 1);

  if(newnode) {
    newnode->list.next       = &node->list;
    newnode->list.prev       = node->list.prev;
       node->list.prev       = &newnode->list;
    newnode->list.prev->next = &newnode->list;
    newnode->list.head       = node->list.head;
    newnode->value           = value;
  }

  return newnode;
}

NODE_TYPEDEF * LIST_METHOD(insert,after)(NODE_TYPEDEF * node, VALUE_TYPEDEF value) {
  NODE_TYPEDEF * newnode = calloc(sizeof(NODE_TYPEDEF), 1);

  if(newnode) {
    newnode->list.prev       = &node->list;
    newnode->list.next       = node->list.next;
       node->list.next       = &newnode->list;
    newnode->list.next->prev = &newnode->list;
    newnode->list.head       = node->list.head;
    newnode->value           = value;
  }

  return newnode;
}

NODE_TYPEDEF * LIST_METHOD(first)(const LIST_TYPEDEF * l) {
  if(l->next == l) { return 0; }
  return (NODE_TYPEDEF *)l->next;
}

NODE_TYPEDEF * LIST_METHOD(last)(const LIST_TYPEDEF * l) {
  if(l->prev == l) { return 0; }
  return (NODE_TYPEDEF *)l->prev;
}

NODE_TYPEDEF * LIST_METHOD(next)(const NODE_TYPEDEF * l) {
  if(l->list.next == l->list.head) { return 0; }
  return (NODE_TYPEDEF *)l->list.next;
}

NODE_TYPEDEF * LIST_METHOD(prev)(const NODE_TYPEDEF * l) {
  if(l->list.prev == l->list.head) { return 0; }
  return (NODE_TYPEDEF *)l->list.prev;
}

