#include "scheduler.cpp"
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

        if (mega_list.Size() == 0)
        {
            delete current;
            current = NULL;
            return IDLE_PROC;
        }
        // update process
        procs[current->origin_index].finish_time = time;
        //
        delete current;
        current = mega_list.GetCurrent();
        mega_list.Remove(false);
        procs[current->origin_index].start_time = time;
        --(current->remaining);
        return current->proc;
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
        sort(procs.begin(), procs.end(), [] (const auto& left, const auto& right) { return left.arrive_time < right.arrive_time });
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

            if (dispatched == IDLE_PROC && arrive_idx >= procs.size() - 1)
            {
                std::cout << "Finished all process!" << std::endl;
                break;
            }
            std::cout << "At time:\t\t" << time << " process\t\t" << dispatched.proc_name << " is working\n";
            ++time;
        }
    }
};
