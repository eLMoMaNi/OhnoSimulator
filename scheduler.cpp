#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <iostream>
#include "megalist.cpp"

// Abstract class for variant Scheduler classes
//
//
class Scheduler
{
protected:
    std::vector<Proc> procs;
    MegaList mega_list; //

public:
    virtual Proc Dispatch(std::vector<MegaNode *> newcomers, int time) = 0;
    virtual void ParallelLoad(std::string filename) = 0;
    void ExitProcess();
};