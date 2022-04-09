#include <scheduler.cpp>

class SJFScheduler : public Scheduler
{
    MegaNode *current;
    Proc Dispatch(std::vector<MegaNode> newcomers, int time)
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
                procs[current->origin_index].start_time=time;
            }
        }

        if (current->remaining > 0)
        {
            --(current->remaining);
            return current->proc;
        }

        if (mega_list.Size() == 1)
        {
            current = NULL;
            return IDLE_PROC;
        }
        // update process
        procs[current->origin_index].finish_time=time;
        //
        current = current->prev;
        procs[current->origin_index].start_time=time;
        --(current->remaining);
        return current->proc;
    }
};
