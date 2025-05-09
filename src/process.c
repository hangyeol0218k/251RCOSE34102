typedef struct IO_process
{
    int io_request_time;
    int io_burst_time;
};

typedef struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    IO_process* io_list;
    int priority;

};
