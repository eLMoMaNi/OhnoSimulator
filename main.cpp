#include <iostream>
#include "sjf_scheduler.cpp"

int main()
{
    // very cool main function
    std::cout << "Welcome to Oh-no Simulator, ain't no OS\n\n";
    SJFScheduler sjf;
    sjf.ParallelLoad("in.txt");
    sjf.PrintStatistics();
}