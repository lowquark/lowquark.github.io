#include "FILENAME.h"

QUEUE_TYPEDEF queue;
VALUE_TYPEDEF value;

QUEUE_METHOD(init)(&queue);

/* enqueue values */
for(i = 0 ; i < 10 ; i ++) {
  QUEUE_METHOD(push)(&queue, value);
}

/* examine first element */
QUEUE_METHOD(peek)(&queue, &value);

/* iterate over all values */
for(i = 0 ; QUEUE_METHOD(at)(&queue, &value, i) ; i ++) {
  /* do something with value... */
}

/* clear values */
QUEUE_METHOD(clear)(&queue);
