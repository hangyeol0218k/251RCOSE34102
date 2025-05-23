#include "process.h"

// process list 생성
Process_data* create_process(int number_of_processes, int max_burst, int max_priority)
{
    srand(time(NULL));
    Process_data* process_data = malloc(sizeof(Process_data)); // Process_data 타입 객체를 하나 생성성

    Process** process_list = (Process **)malloc(sizeof(Process*) * (number_of_processes)); // Process 객체들의 주소 리스트
    for(int i = 0; i < number_of_processes; i++)
    {
        Process* new_process = (Process*)malloc(sizeof(Process));
        *new_process = (Process){i, i, (rand()%max_burst + 1), NULL, (rand()%max_priority + 1), 0, 0};
        process_list[i] = new_process;
    }

    *process_data = (Process_data){process_list, number_of_processes, number_of_processes};

    return process_data;
}

// process list 출력
void print_process_list(Process_data* Process_data)
{
    Process** process_list = Process_data->process_list;
    int n = Process_data->num_of_process;

    // printf("test 1 : %p\n", process_list[0]);

    printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n", "pid", "arrival", "burst", "i/o", "priority", "wait", "turn");
    for (int i = 0; i < n; i++)
    {
        Process* p = process_list[i];
        printf("%d\t%d\t%d\t%p\t%d\t\t%d\t%d\n",
            p->pid, p->arrival_time, p->burst_time, p->io_list, p->priority, p->waiting_time, p->turnaround_time);
    }
}

Process_data* copy_pdata(Process_data* src)    // deep shallow 하는 함수
{
    Process_data* dest = (Process_data*)malloc(sizeof(Process_data));

    dest->num_of_process = src->num_of_process;
    dest->remain_num = src->remain_num;

    dest->process_list = (Process**)malloc(sizeof(Process*) * src->num_of_process);

    for (int i = 0; i < src->num_of_process; i++) {
        dest->process_list[i] = (Process*)malloc(sizeof(Process));

        dest->process_list[i]->pid = src->process_list[i]->pid;
        dest->process_list[i]->arrival_time = src->process_list[i]->arrival_time;
        dest->process_list[i]->burst_time = src->process_list[i]->burst_time;
        dest->process_list[i]->priority = src->process_list[i]->priority;
        dest->process_list[i]->waiting_time = src->process_list[i]->waiting_time;
        dest->process_list[i]->turnaround_time = src->process_list[i]->turnaround_time;

        dest->process_list[i]->io_list = NULL;
    }

    return dest;
}