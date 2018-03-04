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

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define INITIAL_SIZE 32


static void deinit_value(VALUE_TYPEDEF value) {
  /* TODO: Cleanup the VALUE_TYPEDEF, if applicable. This function is called
   * when values are popped from the queue, and when the queue is cleared. */
}


void QUEUE_METHOD(init)(QUEUE_TYPEDEF * q) {
  q->buffer_begin = NULL;
  q->buffer_end = NULL;
  q->getptr = NULL;
  q->putptr = NULL;
  q->size = 0;
}

void QUEUE_METHOD(clear)(QUEUE_TYPEDEF * q) {
  VALUE_TYPEDEF * valptr;

  free(q->buffer_begin);

  /* iterate over [getptr, putptr), call deinit */
  if(q->size) {
    do {
      valptr = q->getptr;

      deinit_value(*valptr);

      valptr ++;
      if(valptr == q->buffer_end) {
        valptr = q->buffer_begin;
      }
    } while(valptr != q->putptr);
  }

  /* clean slate */
  QUEUE_METHOD(init)(q);
}

int QUEUE_METHOD(push)(QUEUE_TYPEDEF * q, VALUE_TYPEDEF value) {
  VALUE_TYPEDEF * new_buffer_begin;
  VALUE_TYPEDEF * wrap_point;
  int new_buffer_size;

  if(!q->buffer_begin) {
    /* this buffer is null */
    q->buffer_begin = malloc(INITIAL_SIZE*sizeof(VALUE_TYPEDEF));

    /* couldn't alloc, escape before anything breaks */
    if(!q->buffer_begin) { return 0; }

    q->buffer_end   = q->buffer_begin + INITIAL_SIZE;
    q->getptr       = q->buffer_begin;
    q->putptr       = q->buffer_begin;
  } else if(q->getptr == q->putptr && q->size != 0) {
    /* full buffer condition */

    /* sanity check */
    assert(q->buffer_end - q->buffer_begin == q->size);

    /* double previous buffer size */
    new_buffer_size = 2*q->size;

    /* alloc new buffer twice as large */
    new_buffer_begin = malloc(new_buffer_size*sizeof(VALUE_TYPEDEF ));

    /* couldn't alloc, escape before anything breaks */
    if(!new_buffer_begin) { return 0; }

    /* pointer within new_buffer where buffer_end lines up with */
    wrap_point = new_buffer_begin + (q->buffer_end - q->putptr);

    /* copy first part [putptr, buffer_end) to new_buffer_begin */
    memcpy(new_buffer_begin, q->putptr, sizeof(VALUE_TYPEDEF)*(q->buffer_end - q->putptr));

    /* copy second part [buffer_begin, putptr) to wrap_point */
    memcpy(wrap_point, q->buffer_begin, sizeof(VALUE_TYPEDEF)*(q->putptr - q->buffer_begin));

    /* new buffer has been initialized, replace old buffer */
    free(q->buffer_begin);

    q->buffer_begin = new_buffer_begin;
    q->buffer_end   = new_buffer_begin + new_buffer_size;
    q->getptr       = new_buffer_begin;
    q->putptr       = new_buffer_begin + q->size;
  }

  /* store at put pointer and advance */
  *q->putptr++ = value;

  /* wrap put pointer at end */
  if(q->putptr == q->buffer_end) {
    q->putptr = q->buffer_begin;
  }

  /* keep track of size */
  q->size ++;

  /* return success */
  return 1;
}

int QUEUE_METHOD(pop)(QUEUE_TYPEDEF * q) {
  if(q->size == 0) { return 0; }

  deinit_value(*q->getptr);

  q->getptr++;

  /* wrap get pointer at end */
  if(q->getptr == q->buffer_end) {
    q->getptr = q->buffer_begin;
  }

  /* keep track of size */
  q->size --;

  return 1;
}

int QUEUE_METHOD(peek)(QUEUE_TYPEDEF * q, VALUE_TYPEDEF * value_out) {
  if(q->size == 0) { return 0; }

  *value_out = *q->getptr;

  return 1;
}

int QUEUE_METHOD(at)(QUEUE_TYPEDEF * q, VALUE_TYPEDEF * value_out, int idx) {
  VALUE_TYPEDEF * elem_ptr;

  if(idx < 0) { return 0; }

  if(idx >= q->size) { return 0; }

  elem_ptr = q->getptr + idx;

  if(elem_ptr >= q->buffer_end) {
    elem_ptr -= q->buffer_end - q->buffer_begin;
  }

  *value_out = *elem_ptr;

  return 1;
}

