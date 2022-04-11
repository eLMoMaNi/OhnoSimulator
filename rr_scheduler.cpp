#include "Headers/scheduler.h"

class RRScheduler : public Scheduler
{
    int time_quantum = 2, timer = 0;
    MegaNode *current = NULL;

    Proc Dispatch(std::vector<MegaNode *> newcomers, int time)
    {
        for (int i = 0; i < newcomers.size(); ++i)
        {
            mega_list.Insert(newcomers[i]);
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

        ++timer;

        if (current->remaining > 0)
        {
            MegaNode *cur = current;

            if (timer == time_quantum)
            {
                mega_list.Next();
                current = mega_list.GetCurrent();

                if (procs[current->origin_index].start_time == -1)
                {
                    procs[current->origin_index].start_time = time + 1;
                }

                if (current != cur)
                {
                    fragments.push_back(current->proc.proc_name);
                }

                timer = 0;
            }

            --(cur->remaining);
            return cur->proc;
        }

        procs[current->origin_index].finish_time = time;

        mega_list.Remove(true);
        delete current;

        if (mega_list.Size() == 0)
        {
            current = NULL;
            return IDLE_PROC;
        }

        current = mega_list.GetCurrent();
        if (procs[current->origin_index].start_time == -1)
        {
            procs[current->origin_index].start_time = time;
        }

        fragments.push_back(current->proc.proc_name);

        timer = 0;

        --(current->remaining);
        return current->proc;
    }
};
