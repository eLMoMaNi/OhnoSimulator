#include <iostream>
#include "sjf_scheduler.cpp"
#include "rr_scheduler.cpp"
int main()
{
    // very cool main function
    std::cout << "Welcome to Oh-no Simulator, ain't no OS\n\n";
    SJFScheduler sjf;
    sjf.ParallelLoad("in.txt");
    sjf.Simulate();
    sjf.PrintStatistics();
    // Example on using RR scheduler
    //RRScheduler rr;
    //rr.ParallelLoad("in.txt");
    //rr.Simulate();
    //rr.PrintStatistics();
}