#include "config.h"

Priority_queue* create_pri_queue(int qsize, int comp)
{
    Priority_queue* newq = (Priority_queue*)malloc(sizeof(Priority_queue));
    int max_size = sizeof(Process*) * (qsize);
    Process** qitems = (Process**)malloc(max_size);

    *newq = (Priority_queue){max_size, -1, qitems, comp}; // tail = -1 (데이터 없음을 표시)

    return newq;
}

int compare(Process* a, Process* b, int key)    // a가 b보다 우선순위가 높은지
{
    switch (key)
    {
    case 0: // arrival time (FCFS)
        return a->arrival_time < b->arrival_time ? 1 : 0;
    case 1: // burst time (SJF)
        if(a->burst_time < b->burst_time) return 1;
        else if(a->burst_time == b->burst_time)
            return a->arrival_time < b->arrival_time ? 1 : 0;   // burst time이 같은 경우 먼저 도착한 것이 우선순위 높음
        else return 0;
    case 2: // priority
        if(a->priority < b->priority) return 1;
        else if(a->priority == b->priority)
            return a->arrival_time < b->arrival_time ? 1 : 0;   // priority가 같은 경우 먼저 도착한 것이 우선순위 높음
        else return 0;
    default:
        printf("[Error] Wrong KEY for compare function\n");
        return -1;
    }
}

void swap_proc(Process** a, Process** b)
{
    Process* temp = *a;
    *a = *b;
    *b = temp;
}

int pri_queue_is_empty(Priority_queue* q)
{
    return (q->tail < 0);
}

int pri_queue_is_full(Priority_queue* q)
{
    return (q->tail >= q->max_size - 1);
}

void push_pri_queue(Priority_queue* pri_queue, Process* proc)
{
    if(pri_queue->tail >= pri_queue->max_size - 1) {
        printf("[ERROR] Priority queue is Full!\n");
        return;
    }

    int t = ++pri_queue->tail;
    int parent = (t - 1)/2;

    Process** qitems = pri_queue->items;    // 포인터 연산을 줄이기 위한 임시 변수
    qitems[t] = proc;
    // printf("t : %d, parent: %d, current: %d\n", t, parent, qitems[t]->pid);
    while (t != 0 && compare(qitems[t], qitems[parent], pri_queue->comp))    // root에 도달하지 않았고, parent보다 우선순위가 높으면
    {
        swap_proc(&qitems[t], &qitems[parent]);
        t = parent;
        parent = (t - 1)/2;
    }
}

Process* pop_pri_queue(Priority_queue* pri_queue)
{
    if(pri_queue->tail < 0) {
        printf("[ERROR] Priority queue is Empty!\n");
        return NULL;
    }

    Process** qitems = pri_queue->items;
    Process* return_process = qitems[0];
    qitems[0] = qitems[pri_queue->tail--];

    int t = 0, smallest = 0;
    int lchild = 2 * t + 1, rchild = 2 * t + 2;
    
    while (lchild <= pri_queue->tail)   // child가 존재하면
    {
        if(compare(qitems[lchild], qitems[t], pri_queue->comp)) {
            smallest = lchild;
        }
        if(rchild <= pri_queue->tail && compare(qitems[rchild], qitems[smallest], pri_queue->comp)) {
            smallest = rchild;
        }

        if(t == smallest) break;
        swap_proc(&qitems[t], &qitems[smallest]);
        t = smallest;
        lchild = 2 * t + 1, rchild = 2 * t + 2;
    }
    return return_process;
}