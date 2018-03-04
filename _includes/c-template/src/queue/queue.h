#ifndef INCLUDE_GUARD_H
#define INCLUDE_GUARD_H

/* FIFO queue of `VALUE_TYPEDEF`s
 */
typedef struct QUEUE_STRUCT {
  VALUE_TYPEDEF * buffer_begin;
  VALUE_TYPEDEF * buffer_end;

  VALUE_TYPEDEF * getptr;
  VALUE_TYPEDEF * putptr;

  int size;
} QUEUE_TYPEDEF;

/* Initializes the given queue to a valid state.
 */
void QUEUE_METHOD(init)(QUEUE_TYPEDEF * q);

/* Deletes all values present in the queue.
 */
void QUEUE_METHOD(clear)(QUEUE_TYPEDEF * q);

/* Pushes a value onto the back of the queue. Reallocates buffer space if necessary.
 *
 * Return Value:
 *   Returns 1 if successful, and 0 if memory allocation failed.
 */
int QUEUE_METHOD(push)(QUEUE_TYPEDEF * q, VALUE_TYPEDEF value);

/* Pops a value from the front of the queue.
 *
 * Return Value:
 *   Returns 1 if a value was popped, and 0 if the queue was empty.
 */
int QUEUE_METHOD(pop)(QUEUE_TYPEDEF * q);

/* Copies the value from the front of the queue into `value_out`.
 *
 * Return Value:
 *   If the queue is empty, returns 0 and leaves `value_out` unmodified.
 *   Returns 1 otherwise.
 */
int QUEUE_METHOD(peek)(QUEUE_TYPEDEF * q, VALUE_TYPEDEF * value_out);

/* Copies the value from the queue at the given index `idx` into `value_out`.
 *
 * Return Value:
 *   If the queue is empty, or if idx is larger than the queue's size, returns
 *   0 and leaves `value_out` unmodified. Returns 1 otherwise.
 *
 * Note:
 *   An index of 0 is the front of the queue. The back of the queue is indexed
 *   by the queue's size minus one.
 */
int QUEUE_METHOD(at)(QUEUE_TYPEDEF * q, VALUE_TYPEDEF * value_out, int idx);

#endif
