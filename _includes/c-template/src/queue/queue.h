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

/*
 * FIFO queue of `VALUE_TYPEDEF`s
 */
typedef struct QUEUE_STRUCT {
  VALUE_TYPEDEF * buffer_begin;
  VALUE_TYPEDEF * buffer_end;

  VALUE_TYPEDEF * getptr;
  VALUE_TYPEDEF * putptr;

  int size;
} QUEUE_TYPEDEF;

/*
 * Initializes the given queue to a valid state.
 */
void QUEUE_METHOD(init)(QUEUE_TYPEDEF * q);

/*
 * Deletes all values present in the queue.
 */
void QUEUE_METHOD(clear)(QUEUE_TYPEDEF * q);

/*
 * Pushes a value onto the back of the queue. Reallocates buffer space if necessary.
 *
 * Return Value:
 *   Returns 1 if successful, and 0 if memory allocation failed.
 */
int QUEUE_METHOD(push)(QUEUE_TYPEDEF * q, VALUE_TYPEDEF value);

/*
 * Pops a value from the front of the queue.
 *
 * Return Value:
 *   Returns 1 if a value was popped, and 0 if the queue was empty.
 */
int QUEUE_METHOD(pop)(QUEUE_TYPEDEF * q);

/*
 * Copies the value from the front of the queue into `value_out`.
 *
 * Return Value:
 *   If the queue is empty, returns 0 and leaves `value_out` unmodified.
 *   Returns 1 otherwise.
 */
int QUEUE_METHOD(peek)(QUEUE_TYPEDEF * q, VALUE_TYPEDEF * value_out);

/*
 * Copies the value from the queue at the given index `idx` into `value_out`.
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
