#include "Headers/proc.h"

Proc::Proc(std::string proc_name, int processing_time, int arrive_time)
{
    this->proc_name = proc_name;
    this->processing_time = processing_time;
    this->arrive_time = arrive_time;
    this->start_time = -1;
    this->finish_time = -1;
}

bool Proc::operator==(const Proc &other)
{
    return other.proc_name==this->proc_name;
}

int Proc::GetResponseTime()
{
    // TODO exp
    return start_time - arrive_time;
}

int Proc::GetTimearound()
{
    // TODO exp if finishtime=-1;
    return finish_time - arrive_time;
}

int Proc::GetDelay()
{
    return GetTimearound() - processing_time;
}