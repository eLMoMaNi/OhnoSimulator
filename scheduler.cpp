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
protected:
    std::vector<Proc> procs; // TODO sort it by arrival time
    MegaList mega_list;      //

public:
    // Parallel load
    Scheduler(std::string filename)
    {
        // for time in N:
        //proc=dispatch(newcomers)
        //  print(for time:{time} the process {proc} is working)
    }

    Scheduler(); // for interactive mode

    virtual Proc Dispatch(std::vector<Proc> newcomers, int time) = 0;
    void ExitProcess();
};