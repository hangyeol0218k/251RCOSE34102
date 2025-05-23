#include "scheduler.h"

void nonpreemptive_schedule(Process_data* process_data, int num_proc, int comp_type)
{
    Priority_queue* ready_queue = create_pri_queue(num_proc, comp_type);

    Process** process_list = process_data->process_list;
    int* n = &(process_data->num_of_process);
    int* remain = &(process_data->remain_num);

    int current_time = 0; // 현재 시간을 나타냄
    int current_exc = -1; // -1: 실행중인 프로세스 없음, else: 현재 실행중인 프로세스의 pid

    while (*remain) // 실행할 프로세스가 남아있는 동안
    {
        for(int i=0; i<*n; i++) { // 현재 시간에 도착한 프로세스들을 모두 ready queue에 넣음
            if(process_list[i]->arrival_time == current_time) {
                push_pri_queue(ready_queue, process_list[i]);
            }
        }

        if(current_exc == -1) {                                 // 실행중인 프로세스가 없으면
            if (!pri_queue_is_empty(ready_queue)) {             // ready queue에 프로세스가 있으면
                Process* new_exc = pop_pri_queue(ready_queue);  // 큐의 front를 꺼내서 실행
                current_exc = new_exc->pid;
            }
        }

        for(int i=0; i<*n; i++) {
            Process* process_i = process_list[i];
            if(current_time >= process_i->arrival_time) { // 도착한 프로세스들은
                if(process_i->burst_time > 0) {           // 아직 끝나지 않았으면
                    process_i->turnaround_time++;         // turnaround time 1만큼 증가
                    if(i != current_exc) {                // 현재 실행 중이 아니면 (ready queue에서 기다리고 있으면)
                        process_i->waiting_time++;        // waiting time 1만큼 증가
                    }
                }
            }
        }

        process_list[current_exc]->burst_time--;        // 실행중 프로세스의 burst time 1만큼 감소
        if(!process_list[current_exc]->burst_time) {    // 끝났으면
            current_exc = -1;
            (*remain)--;
        }
        // if(current_time <= 100){
        //     printf("time: %d, exc: %d, tail: %d, queue:", current_time, current_exc, ready_queue->tail);
        //     for(int i=0; i<=ready_queue->tail; i++) printf("(%d: %d) ", i, ready_queue->items[i]->pid);
        //     printf("\n");
        // }
        
        current_time++;
        // printf("test\n");
    }

    return;
}