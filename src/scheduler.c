#include "scheduler.h"

Log_list* nonpreemptive_schedule(Process_data* process_data, int max_burst, int comp_type)
{
    int* n = &(process_data->num_of_process);

    // Reagy queue 생성
    Priority_queue* ready_queue = create_pri_queue(*n, comp_type);

    // 로그 생성 (for gantt chart)
    Process_log* logs = (Process_log*)malloc(sizeof(Process_log) * (*n) * max_burst * 2);
    Log_list* log_list = (Log_list*)malloc(sizeof(Log_list));
    *log_list = (Log_list){logs, 0};
    int* log_num = &(log_list->log_num);

    Process** process_list = process_data->process_list;
    int* remain = &(process_data->remain_num);

    int current_time = 0; // 현재 시간을 나타냄
    int current_exe = -1; // -1: 실행중인 프로세스 없음, else: 현재 실행중인 프로세스의 pid

    while (*remain) // 실행할 프로세스가 남아있는 동안
    {
        for(int i=0; i<*n; i++) { // 현재 시간에 도착한 프로세스들을 모두 ready queue에 넣음
            if(process_list[i]->arrival_time == current_time) {
                // printf("%d: %d %d\n", current_time, ready_queue->tail, ready_queue->max_size);
                push_pri_queue(ready_queue, process_list[i]);
            }
        }

        if(current_exe == -1) {                                 // 실행중인 프로세스가 없으면
            if (!pri_queue_is_empty(ready_queue)) {             // ready queue에 프로세스가 있으면
                Process* new_exc = pop_pri_queue(ready_queue);  // 큐의 front를 꺼내서 실행
                current_exe = new_exc->pid;
                logs[(*log_num)++] = (Process_log){current_exe, current_time};  // 로그에 프로세스 시작 기록
            }
            else {                                                                                                  // 도착한 프로세스가 아무것도 없으면
                if (*log_num == 0 || logs[(*log_num)-1].pid != -1) logs[(*log_num)++] = (Process_log){current_exe, current_time};    // 로그에 idle 시작 기록
                current_time++;
                continue;
            }
        }

        for(int i=0; i<*n; i++) {
            Process* process_i = process_list[i];
            if(current_time >= process_i->arrival_time) { // 도착한 프로세스들은
                if(process_i->burst_time > 0) {           // 아직 끝나지 않았으면
                    process_i->turnaround_time++;         // turnaround time 1만큼 증가
                    if(i != current_exe) {                // 현재 실행 중이 아니면 (ready queue에서 기다리고 있으면)
                        process_i->waiting_time++;        // waiting time 1만큼 증가
                    }
                }
            }
        }

        process_list[current_exe]->burst_time--;        // 실행중인 프로세스의 burst time 1만큼 감소
        if(!process_list[current_exe]->burst_time) {    // 끝났으면
            current_exe = -1;
            (*remain)--;
        }
        
        current_time++;
    }

    logs[(*log_num)++] = (Process_log){-2, current_time}; // 모든 프로세스 종료 로그

    return log_list;
}

Log_list* preemptive_schedule(Process_data* process_data, int max_burst, int comp_type)
{
    int* n = &(process_data->num_of_process);

    // Reagy queue 생성
    Priority_queue* ready_queue = create_pri_queue(*n, comp_type);

    // 로그 생성 (for gantt chart)
    Process_log* logs = (Process_log*)malloc(sizeof(Process_log) * (*n) * max_burst * 2);
    Log_list* log_list = (Log_list*)malloc(sizeof(Log_list));
    *log_list = (Log_list){logs, 0};
    int* log_num = &(log_list->log_num);

    Process** process_list = process_data->process_list;
    int* remain = &(process_data->remain_num);

    int current_time = 0; // 현재 시간을 나타냄
    int current_exe = -1; // -1: 실행중인 프로세스 없음, else: 현재 실행중인 프로세스의 pid

    while (*remain) // 실행할 프로세스가 남아있는 동안
    {
        for(int i=0; i<*n; i++) { // 현재 시간에 도착한 프로세스들을 모두 ready queue에 넣음
            if(process_list[i]->arrival_time == current_time) {
                // printf("%d: %d %d\n", current_time, ready_queue->tail, ready_queue->max_size);
                push_pri_queue(ready_queue, process_list[i]);
            }
        }

        if(current_exe == -1) {                                 // 실행중인 프로세스가 없을 때
            if (!pri_queue_is_empty(ready_queue)) {             // ready queue에 프로세스가 있으면
                Process* new_exc = pop_pri_queue(ready_queue);  // 큐의 front를 꺼내서 실행
                current_exe = new_exc->pid;
                logs[(*log_num)++] = (Process_log){current_exe, current_time};  // 로그에 프로세스 시작 기록
            }
            else {                                                                                                  // 도착한 프로세스가 아무것도 없으면
                if (*log_num == 0 || logs[(*log_num)-1].pid != -1) logs[(*log_num)++] = (Process_log){current_exe, current_time};    // 로그에 idle 시작 기록
                current_time++;
                continue;
            }
        }
        else {
            if (!pri_queue_is_empty(ready_queue)) {                                         // ready queue에 프로세스가 있으면
                if (compare(ready_queue->items[0], process_list[current_exe], comp_type)) { // front가 실행중 프로세스보다 우선순위가 높으면 
                    Process* new_exc = pop_pri_queue(ready_queue);                          // 꺼내서
                    push_pri_queue(ready_queue, process_list[current_exe]);                 // 원래 프로세스를 다시 ready queue에 넣고
                    current_exe = new_exc->pid;                                             // 새로운 프로세스 실행
                    logs[(*log_num)++] = (Process_log){current_exe, current_time};          // 로그에 프로세스 시작 기록
                }
            }
        }

        for(int i=0; i<*n; i++) {
            Process* process_i = process_list[i];
            if(current_time >= process_i->arrival_time) { // 도착한 프로세스들은
                if(process_i->burst_time > 0) {           // 아직 끝나지 않았으면
                    process_i->turnaround_time++;         // turnaround time 1만큼 증가
                    if(i != current_exe) {                // 현재 실행 중이 아니면 (ready queue에서 기다리고 있으면)
                        process_i->waiting_time++;        // waiting time 1만큼 증가
                    }
                }
            }
        }

        process_list[current_exe]->burst_time--;        // 실행중인 프로세스의 burst time 1만큼 감소
        if(!process_list[current_exe]->burst_time) {    // 끝났으면
            current_exe = -1;
            (*remain)--;
        }
        
        current_time++;
    }

    logs[(*log_num)++] = (Process_log){-2, current_time}; // 모든 프로세스 종료 로그

    return log_list;
}

Log_list* rr_schedule(Process_data* process_data, int max_burst, int comp_type, int quantum)
{
    int* n = &(process_data->num_of_process);

    // Reagy queue 생성
    Queue* ready_queue = create_queue(*n + 1);  // 원형 큐 구조상

    // 로그 생성 (for gantt chart)
    Process_log* logs = (Process_log*)malloc(sizeof(Process_log) * (*n) * max_burst * 2);
    Log_list* log_list = (Log_list*)malloc(sizeof(Log_list));
    *log_list = (Log_list){logs, 0};
    int* log_num = &(log_list->log_num);

    Process** process_list = process_data->process_list;
    int* remain = &(process_data->remain_num);

    int current_time = 0;   // 현재 시간을 나타냄
    int current_exe = -1;   // -1: 실행중인 프로세스 없음, else: 현재 실행중인 프로세스의 pid
    int timecheck = 0;      // time quantum을 체크하기 위한 변수

    while (*remain) // 실행할 프로세스가 남아있는 동안
    {
        for(int i=0; i<*n; i++) { // 현재 시간에 도착한 프로세스들을 모두 ready queue에 넣음
            if(process_list[i]->arrival_time == current_time) {
                push_queue(ready_queue, process_list[i]);
            }
        }
        
        // 실행중인 프로세스가 없을 때
        if(current_exe == -1) {                                 
            if (!queue_is_empty(ready_queue)) {                                 // ready queue에 프로세스가 있으면
                Process* new_exc = pop_queue(ready_queue);                      // 큐의 front를 꺼내서 실행
                current_exe = new_exc->pid;
                timecheck = 0;
                logs[(*log_num)++] = (Process_log){current_exe, current_time};  // 로그에 프로세스 시작 기록
            }
            else {                                                                                                  // 도착한 프로세스가 아무것도 없으면
                if (*log_num == 0 || logs[(*log_num)-1].pid != -1) logs[(*log_num)++] = (Process_log){current_exe, current_time};    // 로그에 idle 시작 기록
                current_time++;
                continue;
            }
        }
        // 실행중인 프로세스가 있을 때
        else {
            if (!queue_is_empty(ready_queue)) {                                     // ready queue에 프로세스가 있으면
                if (timecheck == quantum) {                                         // 기존 프로세스가 time quantum 소진했으면
                    Process* new_exc = pop_queue(ready_queue);                      // 꺼내서
                    push_queue(ready_queue, process_list[current_exe]);             // 원래 프로세스를 다시 ready queue에 넣고
                    current_exe = new_exc->pid;                                     // 새로운 프로세스 실행
                    timecheck = 0;
                    logs[(*log_num)++] = (Process_log){current_exe, current_time};  // 로그에 프로세스 시작 기록
                }
            }
        }
        
        for(int i=0; i<*n; i++) {
            Process* process_i = process_list[i];
            if(current_time >= process_i->arrival_time) { // 도착한 프로세스들은
                if(process_i->burst_time > 0) {           // 아직 끝나지 않았으면
                    process_i->turnaround_time++;         // turnaround time 1만큼 증가
                    if(i != current_exe) {                // 현재 실행 중이 아니면 (ready queue에서 기다리고 있으면)
                        process_i->waiting_time++;        // waiting time 1만큼 증가
                    }
                }
            }
        }
        
        process_list[current_exe]->burst_time--;        // 실행중인 프로세스의 burst time 1만큼 감소
        if(!process_list[current_exe]->burst_time) {    // 끝났으면
            current_exe = -1;
            (*remain)--;
        }
        
        timecheck++;
        current_time++;
    }

    logs[(*log_num)++] = (Process_log){-2, current_time}; // 모든 프로세스 종료 로그

    return log_list;
}