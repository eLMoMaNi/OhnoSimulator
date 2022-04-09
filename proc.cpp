#include <string>
struct Proc
{
    std::string proc_name;
    int processing_time;
    int arrive_time;
    int start_time;
    int finish_time;

    Proc(std::string proc_name, int processing_time, int arrive_time)
    {
        this->proc_name = proc_name;
        this->processing_time = processing_time;
        this->arrive_time = arrive_time;
        this->start_time = -1;
        this->finish_time = -1;
    }

    //override logical equality operator. proc name acts as PID
    bool operator==(const Proc &other)
    {
        return other.proc_name==this->proc_name;
    }

    int GetResponseTime()
    {
        // TODO exp
        return start_time - arrive_time;
    }

    int GetTimearound()
    {
        // TODO exp if finishtime=-1;
        return finish_time - arrive_time;
    }

    int GetDelay()
    {
        return GetTimearound() - processing_time;
    }
};
const Proc IDLE_PROC = Proc("IDLE", -1, -1);