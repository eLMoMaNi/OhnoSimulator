#include "Headers/scheduler.h"

bool Scheduler::CompByArrive(const Proc &l, const Proc &r)
{
    return l.arrive_time < r.arrive_time;
}

bool Scheduler::CompByFinish(const Proc &l, const Proc &r)
{
    return l.finish_time < r.finish_time;
}

void Scheduler::ParallelLoad(std::string filename)
{

    std::ifstream file(filename);

    if (!(file.good())){
        std::cerr<<"File does NOT exist!";
        return;
    }

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
}

void Scheduler::InteractiveLoad()
{
    bool done = false;
    int time = 0;
    while (!done)
    {
        // getting processes and simulating them
        while (true)
        {
            // getting new commers
            std::cout << "At Time: " << time << " Enter comming process(name processingtime. eg Chrome 10 ) or type EXIT:\n";
            std::string proc_name;
            int processing_time;
            std::cin >> proc_name;
            if (proc_name == "NEXT")
                break;

            if (proc_name == "EXIT")
            {
                done = true;
                break;
            }
            std::cin >> processing_time;
            Proc proc(proc_name, processing_time, time);
            procs.push_back(proc);
        }
        Simulate(true, time);
        ++time;
    }
}

void Scheduler::Simulate(bool interactive, int time)
{
    int arrive_idx = 0;
    //int time = 0;

    while (true)
    {
        // Get newcomers
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
            std::cout << "\nFinished all processes!\n"
                      << std::endl;
            break;
        }

        std::cout << "At time: " << time << "\t process " << dispatched.proc_name << " is working\n";

        ++time;

        if (interactive)
        {
            break;
        }
    }
}

void Scheduler::PrintStatistics()
{
    // std::vector<Proc> tmp_vec = procs;
    // std::sort(tmp_vec.begin(), tmp_vec.end(), CompByFinish);

    std::cout << "Processes Order: ";
    for (int i = 0; i < fragments.size(); ++i)
    {
        // Proc proc = tmp_vec[i];
        // std::cout << proc.proc_name;

        std::cout << fragments[i] << ' ';
    }

    for (int i = 0; i < procs.size(); i++)
    {
        Proc proc = procs[i];
        std::cout << "\nProcess: " << proc.proc_name << "\t Response: " << proc.GetResponseTime() << "\t TA: " << proc.GetTimearound() << "\t Delay: " << proc.GetDelay();
    }
}