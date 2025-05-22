#include "config.h"

// ---- ---- ---- ---- Queue functions ---- ---- ---- ----
Queue* create_queue(int qsize)
{
    Queue* newq = (Queue*)malloc(sizeof(Queue));
    Process** qitems = (Process**)malloc(sizeof(Process*) * (qsize + 1));  // 배열 큐의 한계로 인해 프로세스 수보다 1 크게 설정

    *newq = (Queue){qsize + 1, 0, 0, qitems};

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
        printf("[Error] Queue is Full!\n");
        return;
    }
    q->itmes[q->tail++] = proc;
    
    return;
}

Process* pop_queue(Queue* q)
{
    if (queue_is_empty(q)) {
        printf("[Error] Queue is Empty!\n");
        return NULL;
    }

    return(q->itmes[(q->head)++]);
}

// ---- ---- ---- ---- Priority queue functions ---- ---- ---- ----
Priority_queue* create_pri_queue(int qsize)
{
    Priority_queue* newq = (Priority_queue*)malloc(sizeof(Priority_queue));
    int max_size = sizeof(Process*) * (qsize);
    Process** qitems = (Process**)malloc(max_size);

    *newq = (Priority_queue){max_size, -1, qitems}; // tail = -1 (데이터 없음을 표시)

    return newq;
}

void swap_proc(Process* a, Process* b)
{
    Process* temp = a;
    a = b;
    b = temp;
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

    while (t != 0 && qitems[t]->priority < qitems[parent]->priority)    // root에 도달하지 않았고, parent보다 우선순위가 높으면
    {
        swap_proc(qitems[t], qitems[parent]);
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
        if(qitems[t]->priority > qitems[lchild]->priority) {
            smallest = lchild;
        }
        if(rchild <= pri_queue->tail && qitems[smallest]->priority > qitems[rchild]->priority) {
            smallest = rchild;
        }

        if(t == smallest) break;
        swap_proc(qitems[t], qitems[smallest]);
        t = smallest;
    }
    return return_process;
}