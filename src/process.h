#ifndef PROCESS_H
#define PROCESS_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct _IO_process
{
    int io_request_time;
    int io_burst_time;
} IO_process;

typedef struct _Process
{
    int pid;
    int arrival_time;
    int burst_time;
    IO_process* io_list;
    int priority;           // priority 값이 작을수록 우선순위가 높다고 가정
    int waiting_time;
    int turnaround_time;
} Process;

typedef struct _Process_data
{
    Process** process_list;
    int num_of_process;
    int remain_num;
} Process_data;

Process_data* create_process(int, int);
void print_process_list(Process_data*);

#endif