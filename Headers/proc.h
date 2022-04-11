#include <string>

struct Proc
{
    std::string proc_name;
    
    int processing_time;
    int arrive_time;
    int start_time;
    int finish_time;

    Proc(std::string proc_name, int processing_time, int arrive_time);

    // Override logical equality operator; proc_name acts as PID
    bool operator==(const Proc &other);

    // Returns the proccess' response time
    int GetResponseTime();

    // Returns the proccess' timearound
    int GetTimearound();

    // Returns the proccess' delay
    int GetDelay();
};

const Proc IDLE_PROC = Proc("IDLE", -1, -1);