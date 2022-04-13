#ifndef EXAMPLE_GENERATOR
#define EXAMPLE_GENERATOR
#include <iostream>
#include <fstream>
#include <random>
#include <string>

void GenerateFile(int n, int max_processing=10, int max_arrive=10, std::string filename="in.txt"){    
    //create file
    std::ofstream file(filename);
    file<<n;
    std::srand((unsigned int)time(NULL)) ;
    char name='A';
    for (int i=0;i<n;i++)
    {
        //create the process
        int processing_time=1 + ( std::rand() % ( max_processing - 1 + 1 ) );
        int arrive_time=1 + ( std::rand() % ( max_arrive - 1 + 1 ) );

        file<<std::endl<<(std::to_string(arrive_time)+" "+std::to_string(processing_time));

        
        ++name;
    }
    file.close();

}

#endif