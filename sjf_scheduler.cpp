#include "Headers/scheduler.h"
#include <algorithm>
class SJFScheduler : public Scheduler
{
    MegaNode *current = NULL;
    Proc Dispatch(std::vector<MegaNode *> newcomers, int time)
    {
        for (int i = 0; i < newcomers.size(); i++)
        {
            mega_list.InsertSorted(newcomers[i]);
        }

        if (current == NULL) // if first time or idle
        {
            if (mega_list.Size() == 0)
            {
                return IDLE_PROC;
            }
            else
            {
                current = mega_list.GetCurrent();
                mega_list.Remove(false);
                procs[current->origin_index].start_time = time;
            }
        }

        if (current->remaining > 0)
        {

            --(current->remaining);
            return current->proc;
        }

        procs[current->origin_index].finish_time = time;
        if (mega_list.Size() == 0)
        {
            delete current;
            current = NULL;
            return IDLE_PROC;
        }
        // update process
        //
        delete current;
        current = mega_list.GetCurrent();
        mega_list.Remove(false);
        procs[current->origin_index].start_time = time;
        --(current->remaining);
        return current->proc;
    }
    static bool CompByFinish(const Proc &l, const Proc &r)
    {
        return l.finish_time < r.finish_time;
    }
    static bool CompByArrive(const Proc &l, const Proc &r)
    {
        return l.arrive_time < r.arrive_time;
    }

public:
    void ParallelLoad(std::string filename)
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
        std::sort(procs.begin(), procs.end(), CompByArrive);
        int arrive_idx = 0; // index to procs to flow by arrive time
        int time = 0;
        while (true)
        {
            // get newcomers
            std::vector<MegaNode *> newcomers;
            while (procs[arrive_idx].arrive_time <= time && arrive_idx < procs.size())
            {
                MegaNode *proc_node = new MegaNode(procs[arrive_idx], procs[arrive_idx].processing_time, arrive_idx);
                newcomers.push_back(proc_node);
                ++arrive_idx;
            }
            Proc dispatched = Dispatch(newcomers, time);

            if (dispatched == IDLE_PROC && arrive_idx > procs.size() - 1)
            {
                std::cout << "\nFinished all processes!\n" << std::endl;
                break;
            }
            std::cout << "At time: " << time << "\t process " << dispatched.proc_name << " is working\n";
            ++time;
        }
    }

    void PrintStatistics()
    {
        std::vector<Proc> tmp_vec = procs;
        std::sort(tmp_vec.begin(), tmp_vec.end(), CompByFinish);
        std::cout << "Processes Order: ";
        for (int i = 0; i < tmp_vec.size(); i++)
        {
            Proc proc = tmp_vec[i];
            std::cout << proc.proc_name;
        }
        for (int i = 0; i < procs.size(); i++)
        {
            Proc proc = procs[i];
            std::cout << "\nProcess: " << proc.proc_name << "\t Response: " << proc.GetResponseTime() << "\t TA: " << proc.GetTimearound() << "\t Delay: " << proc.GetDelay();
        }
    }
};
