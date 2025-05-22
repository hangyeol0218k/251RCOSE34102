#include "process.h"
#include "config.h"
#include "scheduler.h"

#define MAX_BURST 20 // 최대 CPU burst time
#define NUM_OF_PROCESS 10 // process 개수

int debug = 0;

int main()
{
    Process_data* process_data = create_process(NUM_OF_PROCESS, MAX_BURST); // process list 생성
    print_process_list(process_data);

    // fcfs
    // Process_data data_fcfs = *process_data;
    // Queue* ready_queue_fcfs = create_queue(NUM_OF_PROCESS);
    // fcfs(&data_fcfs, ready_queue_fcfs);
    // print_process_list(&data_fcfs);

    // priority
    Process_data data_pri = *process_data;
    Priority_queue* ready_queue_pri = create_pri_queue(NUM_OF_PROCESS);
    priority_schedule(&data_pri, ready_queue_pri);
    print_process_list(&data_pri);

    return 0;
}