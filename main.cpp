#include <iostream>
#include "sjf_scheduler.cpp"
#include "rr_scheduler.cpp"
#include "example_generator.h"




int main()
{
    // very cool main function
    std::cout << "Welcome to Oh-no Simulator, ain't no OS\n\n";
    SJFScheduler sjf;
    int NUMBER_OF_FILES=10;
    for (int i=0;i<NUMBER_OF_FILES;i++)
    {
    //generate random processes file
    GenerateFile(2);
    sjf.ParallelLoad("in.txt");
    sjf.Simulate();
    sjf.PrintStatistics();
    }

    // Example on using RR scheduler
    //RRScheduler rr;
    //rr.ParallelLoad("in.txt");
    //rr.Simulate();
    //rr.PrintStatistics();
}