#ifndef CONFIG_H
#define CONFIG_H

#include "process.h"

typedef struct _Queue
{
    int size; // 실제 사용 가능 공간은 size-1
    int head; // first element의 위치
    int tail; // last element의 다음 위치
    Process** itmes;
} Queue;

typedef struct _Priority_queue  // index 0 ~ n-1 을 사용하는 우선순위 큐 (min heap 기반)
{
    int max_size;   // 최대 element 개수
    int tail;       // 마지막 원소의 인덱스
    Process** items;
    int comp;       // 비교 기준을 결정 (0: arrival time, 1: burst time, 2: priority)
} Priority_queue;

Queue* create_queue(int);
int queue_is_empty(Queue*);
int queue_is_full(Queue*);
void push_queue(Queue*, Process*);
Process* pop_queue(Queue*);

Priority_queue* create_pri_queue(int, int);
int compare(Process*, Process*, int);
void swap_proc(Process**, Process**);
int pri_queue_is_empty(Priority_queue*);
int pri_queue_is_full(Priority_queue*);
void push_pri_queue(Priority_queue*, Process*);
Process* pop_pri_queue(Priority_queue*);

#endif