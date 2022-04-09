#include <queue>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <fstream>

#include "megalist.cpp"

// Abstract class for variant Scheduler classes
//
//
class Scheduler
{
    std::vector<Proc> procs; // TODO sort it by arrival time
    MegaList mega_list;      //

public:
    // Parallel load
    Scheduler(std::string filename)
    {

    }

    Scheduler();    //for interactive mode

    virtual Proc Dispatch() = 0;
    void ExitProcess();
};