#ifndef INCLUDE_GUARD_H
#define INCLUDE_GUARD_H

typedef struct QUEUE_STRUCT {
  VALUE_TYPEDEF * buffer_begin;
  VALUE_TYPEDEF * buffer_end;

  VALUE_TYPEDEF * getptr;
  VALUE_TYPEDEF * putptr;

  int size;
} QUEUE_TYPEDEF;

void QUEUE_METHOD(init)  (QUEUE_TYPEDEF * q);
void QUEUE_METHOD(clear) (QUEUE_TYPEDEF * q);

int  QUEUE_METHOD(push)  (QUEUE_TYPEDEF * q, VALUE_TYPEDEF element);
int  QUEUE_METHOD(pop)   (QUEUE_TYPEDEF * q);

int  QUEUE_METHOD(peek)  (QUEUE_TYPEDEF * q, VALUE_TYPEDEF * element_out);
int  QUEUE_METHOD(at)    (QUEUE_TYPEDEF * q, VALUE_TYPEDEF * element_out, int idx);

#endif
