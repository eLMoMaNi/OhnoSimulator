#include "Headers/scheduler.h"

class FIFOScheduler : public Scheduler
{
    MegaNode *current = NULL;
    Proc Dispatch(std::vector<MegaNode *> newcomers, int time)
    {
        for (int i = 0; i < newcomers.size(); ++i)
        {
            mega_list.InsertBack(newcomers[i]);
        }

        if (current == NULL)
        {
            if (mega_list.Size() == 0)
            {
                return IDLE_PROC;
            }
            else
            {
                current = mega_list.GetCurrent();
                procs[current->origin_index].start_time = time;

                fragments.push_back(current->proc.proc_name);
            }
        }

        if (current->remaining > 0)
        {

            --(current->remaining);
            return current->proc;
        }

        procs[current->origin_index].finish_time = time;

        mega_list.Remove(false);
        delete current;

        if (mega_list.Size() == 0)
        {
            current = NULL;
            return IDLE_PROC;
        }

        current = mega_list.GetCurrent();
        procs[current->origin_index].start_time = time;

        fragments.push_back(current->proc.proc_name);

        --(current->remaining);

        return current->proc;
    }
};
