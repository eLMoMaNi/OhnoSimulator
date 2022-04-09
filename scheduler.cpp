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
    // Parallel load
    Scheduler(std::string filename)
    {
        // for time in N:
        // proc=dispatch(newcomers)
        //  print(for time:{time} the process {proc} is working)

        // load processes from a file parallelly
        std::ifstream file(filename);
        int n;
        file >> n;
        for (int i = 0; i < n; i++)
        {
            std::string proc_name;
            int arrive_time, processing_time;
            file >> proc_name >> arrive_time >> processing_time;
            Proc proc(proc_name, processing_time, arrive_time);
            procs.push_back(proc);
        }
        // todo sort procs by arrive time
        int arrive_idx = 0; // index to procs to flow by arrive time
        int time = 0;
        while (true)
        {
            // get newcomers
            std::vector<MegaNode> newcomers;
            while (procs[arrive_idx].arrive_time <= time)
            {
                MegaNode proc_node(procs[arrive_idx], procs[arrive_idx].processing_time, arrive_idx);
                newcomers.push_back(proc_node);
                ++arrive_idx;
            }
            Proc dispatched = Dispatch(newcomers, time);
            
            if (dispatched == IDLE_PROC && arrive_idx == procs.size()-1)
            {   
                std::cout<<"Finished all process!"<<std::endl;
                break;
            }
            std::cout<<"At time:\t\t"<<time<<" process\t\t"<<dispatched.proc_name<<" is working\n";
            ++time;
        }
    }

    Scheduler(); // for interactive mode

    virtual Proc Dispatch(std::vector<MegaNode> newcomers, int time) = 0;
    void ExitProcess();
};