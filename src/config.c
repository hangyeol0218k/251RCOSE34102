#include "config.h"

Queue* create_queue(int qsize)
{
    Queue* newq = (Queue*)malloc(sizeof(Queue));
    Process** qitems = (Process**)malloc(sizeof(Process*) * qsize);

    *newq = (Queue){qsize, 0, 0, qitems};

    return newq;
}

int queue_is_empty(Queue* q)
{
    return (q->head == q->tail);
}

int queue_is_full(Queue* q)
{
    return ((q->tail + 1)%(q->size) == q->head);
}

void push_queue(Queue* q, Process* proc)
{
    if (queue_is_full(q)) {
        printf("[Error] Queue is Full!");
        return;
    }
    q->itmes[q->tail++] = proc;
    
    return;
}

Process* pop_queue(Queue* q)
{
    if (queue_is_empty(q)) {
        printf("[Error] Queue is Empty!");
        return NULL;
    }

    return(q->itmes[(q->head)++]);
}