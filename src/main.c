#include "process.h"
#include "config.h"
#include "scheduler.h"

#define MAX_BURST 20        // 최대 CPU burst time
#define NUM_OF_PROCESS 5    // process 개수
#define MAX_PRIORITY 10     // priority 최댓값

int debug = 0;

int main()
{
    Process_data* process_data = create_process(NUM_OF_PROCESS, MAX_BURST, MAX_PRIORITY); // process list 생성

    printf("[Initial Processes]\n");
    print_process_list(process_data);

    // ---- ---- ---- ---- FCFS ---- ---- ---- ----
    Process_data* data_fcfs = copy_pdata(process_data);
    nonpreemptive_schedule(data_fcfs, NUM_OF_PROCESS, 0);

    printf("\n[After FCFS]\n");
    print_process_list(data_fcfs);

    // ---- ---- ---- ---- SJF ---- ---- ---- ----
    Process_data* data_sjf = copy_pdata(process_data);
    nonpreemptive_schedule(data_sjf, NUM_OF_PROCESS, 1);

    printf("\n[After SJF]\n");
    print_process_list(data_sjf);

    // ---- ---- ---- ---- priority ---- ---- ---- ----
    Process_data* data_pri = copy_pdata(process_data);
    nonpreemptive_schedule(data_pri, NUM_OF_PROCESS, 2);

    printf("\n[After Priority scheduling]\n");
    print_process_list(data_pri);

    free(process_data);

    return 0;
}