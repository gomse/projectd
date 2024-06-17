/**
    @file   d_queue.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_QUEUE_H_
#define DOROTHY_QUEUE_H_

typedef struct D_Queue {
    Uint32 count;
    void *i, *o;
} DQueue;

BEGIN_DOROTHY_API
    void    D_PushQueue(DQueue *q, void *data);
    void*   D_PopQueue(DQueue *q);
END_DOROTHY_API

#endif
