#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "megalist.h"

// Abstract class for variant Scheduler classes
class Scheduler
{
protected:
    std::vector<Proc> procs;
    std::vector<std::string> fragments;

    MegaList mega_list; 

public:
    virtual Proc Dispatch(std::vector<MegaNode *> newcomers, int time) = 0;
    
    static bool CompByFinish(const Proc &l, const Proc &r);
    static bool CompByArrive(const Proc &l, const Proc &r);

    void ParallelLoad(std::string filename);
    void Simulate(bool interactive = false,int time=0);
    void InteractiveLoad();
    void PrintStatistics();
    void ExitProcess();
};

#endif
