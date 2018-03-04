#include "FILENAME.h"

int i;
VALUE_TYPEDEF value;
QUEUE_TYPEDEF queue;

/* initialize queue */
QUEUE_METHOD(init)(&queue);

/* enqueue values */
for(i = 0 ; i < 10 ; i ++) {
  VALUE_TYPEDEF new_value;

  /* ... */

  /* place in queue */
  QUEUE_METHOD(push)(&queue, new_value);
}

/* examine first element */
if(QUEUE_METHOD(peek)(&queue, &value)) {
  /* ... */
}

/* iterate over all values */
for(i = 0 ; QUEUE_METHOD(at)(&queue, &value, i) ; i ++) {
  /* ... */
}

/* clear values */
QUEUE_METHOD(clear)(&queue);
