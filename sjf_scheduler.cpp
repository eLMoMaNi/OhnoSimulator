#include "Headers/scheduler.h"

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
};
