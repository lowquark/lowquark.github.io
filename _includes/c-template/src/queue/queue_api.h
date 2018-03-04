typedef struct QUEUE_STRUCT QUEUE_TYPEDEF;

void QUEUE_METHOD(init)  (QUEUE_TYPEDEF * q);

void QUEUE_METHOD(clear) (QUEUE_TYPEDEF * q);

int  QUEUE_METHOD(push)  (QUEUE_TYPEDEF * q, VALUE_TYPEDEF value);

int  QUEUE_METHOD(pop)   (QUEUE_TYPEDEF * q);

int  QUEUE_METHOD(peek)  (QUEUE_TYPEDEF * q, VALUE_TYPEDEF * value_out);

int  QUEUE_METHOD(at)    (QUEUE_TYPEDEF * q, VALUE_TYPEDEF * value_out, int idx);
