#ifndef CONFIG_H
#define CONFIG_H

#include "process.h"

typedef struct _Queue
{
    int size; // 실제 사용 가능 공간: size-1
    int head; // first element의 위치
    int tail; // last element의 다음 위치
    Process** itmes;

} Queue;

Queue* create_queue(int);
int queue_is_empty(Queue*);
int queue_is_full(Queue*);
void push_queue(Queue*, Process*);
Process* pop_queue(Queue*);

#endif