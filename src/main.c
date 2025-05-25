#include "process.h"
#include "config.h"
#include "scheduler.h"
#include "evaluation.h"

#define MAX_BURST 10            // 최대 CPU burst time
#define NUM_OF_PROCESS 15       // process 개수
#define MAX_PRIORITY 20         // priority 최댓값
#define NUM_OF_ALGORITHMS 6     // 사용할 scheduling 종류의 수
#define MAX_ARRIVAL_TIME 150    // 최대 arrival time
int debug = 0;

int main()
{
    Process_data* process_data = create_process(NUM_OF_PROCESS, MAX_BURST, MAX_PRIORITY, MAX_ARRIVAL_TIME); // process list 생성

    printf("[Initial Processes]\n");
    print_process_list(process_data);

    // ---- ---- ---- ---- FCFS ---- ---- ---- ----
    Process_data* data_fcfs = copy_pdata(process_data);
    Log_list* log_fcfs = nonpreemptive_schedule(data_fcfs, MAX_BURST, 0);

    printf("\n[After FCFS]\n");
    print_process_list2(process_data, data_fcfs);
    print_gantt_chart(log_fcfs);

    // ---- ---- ---- ---- SJF ---- ---- ---- ----
    Process_data* data_sjf = copy_pdata(process_data);
    Log_list* log_sjf = nonpreemptive_schedule(data_sjf, MAX_BURST, 1);

    printf("\n[After SJF]\n");
    print_process_list2(process_data, data_sjf);
    print_gantt_chart(log_sjf);

    // ---- ---- ---- ---- priority ---- ---- ---- ----
    Process_data* data_pri = copy_pdata(process_data);
    Log_list* log_pri = nonpreemptive_schedule(data_pri, MAX_BURST, 2);

    printf("\n[After Priority scheduling]\n");
    print_process_list2(process_data, data_pri);
    print_gantt_chart(log_pri);

    // ---- ---- ---- ---- Evaluation ---- ---- ---- ----
    char* names[NUM_OF_ALGORITHMS] = {"FCFS", "SJF", "Priority", "FCFS", "FCFS", "FCFS"};
    Process_data* result_list[NUM_OF_ALGORITHMS] = {data_fcfs, data_sjf, data_pri, data_fcfs, data_fcfs, data_fcfs};

    print_eval(result_list, names, NUM_OF_ALGORITHMS, NUM_OF_PROCESS);
    // ---- ---- ---- ---- End of Program ---- ---- ---- ----
    free(process_data);
    free(data_fcfs); free(log_fcfs);
    free(data_sjf); free(log_sjf);
    free(data_pri); free(log_pri);
    
    return 0;
}