#ifndef FCFS_H
#define FCFS_H

#include "process.h"
#include "config.h"

typedef struct _Process_log {
    int pid;
    int time;
} Process_log;

typedef struct _Log_list
{
    Process_log* logs;
    int log_num;
} Log_list;

Log_list* nonpreemptive_schedule(Process_data*, int, int);

#endif