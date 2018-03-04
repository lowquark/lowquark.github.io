#ifndef INCLUDE_GUARD_H
#define INCLUDE_GUARD_H

typedef struct LIST_STRUCT {
  struct LIST_STRUCT * next;
  struct LIST_STRUCT * prev;
  struct LIST_STRUCT * head;
} LIST_TYPEDEF;

typedef struct NODE_STRUCT {
  LIST_TYPEDEF list;
  VALUE_TYPEDEF value;
} NODE_TYPEDEF;

/*
 *  +----------------------------------------------+
 *  |  +-------+  +-------+  +-------+  +-------+  |
 *  +->| list  |->| list  |->| list  |->| list  |--+
 *     +-------+  + - - - +  + - - - +  + - - - +
 *                | value |  | value |  | value |
 *                +-------+  +-------+  +-------+
 *                  node       node       node
 */

void LIST_METHOD(init)  (LIST_TYPEDEF * l);
void LIST_METHOD(clear) (LIST_TYPEDEF * l);

void LIST_METHOD(erase) (NODE_TYPEDEF * node);

/* creates a new node with value `value` and inserts it at the back of the list */
NODE_TYPEDEF * LIST_METHOD(push,back)  (LIST_TYPEDEF * l, VALUE_TYPEDEF value);
/* creates a new node with value `value` and inserts it at the front of the list */
NODE_TYPEDEF * LIST_METHOD(push,front) (LIST_TYPEDEF * l, VALUE_TYPEDEF value);

/* creates a new node with value `value` and inserts it before `node` */
NODE_TYPEDEF * LIST_METHOD(insert,before) (NODE_TYPEDEF * node, VALUE_TYPEDEF value);
/* creates a new node with value `value` and inserts it after `node` */
NODE_TYPEDEF * LIST_METHOD(insert,after)  (NODE_TYPEDEF * node, VALUE_TYPEDEF value);

NODE_TYPEDEF * LIST_METHOD(first) (const LIST_TYPEDEF * l);
NODE_TYPEDEF * LIST_METHOD(last)  (const LIST_TYPEDEF * l);

NODE_TYPEDEF * LIST_METHOD(next)  (const NODE_TYPEDEF * l);
NODE_TYPEDEF * LIST_METHOD(prev)  (const NODE_TYPEDEF * l);

#endif
