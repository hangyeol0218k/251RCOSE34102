#include "evaluation.h"

void print_eval(Process_data** results, char** names, int num_of_algorithms, int num_of_processes)
{
    int n = num_of_algorithms;
    int m = num_of_processes;

    float* wt_list = (float*)malloc(sizeof(float) * n);
    float* tt_list = (float*)malloc(sizeof(float) * n);

    for(int i = 0; i < n; i++) {
        Process** list = results[i]->process_list;
        int sum_w = 0, sum_t = 0;

        for(int j = 0; j < m; j++) {
            sum_w += list[j]->waiting_time;
            sum_t += list[j]->turnaround_time;
        }

        wt_list[i] = ((float)sum_w) / ((float)m);
        tt_list[i] = ((float)sum_t) / ((float)m);
    }

    // line 1
    printf("%26s", "");
    for(int i = 0; i < 73; i++) printf("-");
    printf("\n");

    // line 2
    printf("%26s", "");
    for(int i = 0; i < n; i++) {
        printf("|%10s ", names[i]);
    }
    printf("|\n");

    // line 3
    for(int i = 0; i < 99; i++) printf("-");
    printf("\n");

    //line 4
    printf("|%-25s", " Avg. Waiting Time");

    for(int i = 0; i < n; i++) {
        printf("|%10.3f ", wt_list[i]);
    }
    printf("|\n");

    //line 5
    printf("|%-25s", " Avg. Turnarround Time");

    for(int i = 0; i < n; i++) {
        printf("|%10.3f ", tt_list[i]);
    }
    printf("|\n");

    // line 6
    for(int i = 0; i < 99; i++) printf("-");
    printf("\n");
}

void print_gantt_chart(Log_list* log_list)
{
    Process_log* pl = log_list->logs;

    printf("[Gantt chart]\n");

    for (int i = 0; i < log_list->log_num; i++) {
        printf("|");
        switch(pl[i].pid) {
            case -2:
                break;
            case -1:
                printf(" idle "); break;
            default:
                printf(" P");
                printf("%d ", pl[i].pid);
        }
    } printf("\n");

    for (int i = 0; i < log_list->log_num; i++) {
        printf("%-3d", pl[i].time);
        if(pl[i].pid == -2) ;  // do nothing
        else if(pl[i].pid == -1) {  
            printf("    ");
        }
        else if(pl[i].pid > 9) {
            printf("   ");
        }
        else {
            printf("  ");
        }
    }
    printf("\n");
}