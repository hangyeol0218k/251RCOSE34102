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

    Queue* ready_queue = create_queue(NUM_OF_PROCESS + 1); // 배열 큐의 한계로 인해 최대 저장 가능 개수보다 1 크게 설정

    fcfs(process_data, ready_queue);

    print_process_list(process_data);
    return 0;
}