
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

int main() 
{
    std::string path = "spiffs_data/sensors.config";
    unsigned int lines = 0;
    std::ifstream infile(path);
    if( !infile  ) {
       std::cout << ("Can't open file!");
    } else {
        std::cout <<("File opened.");
    }
        std::cout <<("\n");
    
    std::string line;
    while (std::getline(infile, line))
    {
        lines++;
        std::cout <<("Line ");
        std::cout <<(lines);
        std::cout <<(": ");
        std::cout <<(line.c_str());
        std::cout <<("\n");
        /*
        std::istringstream iss(line);
        int a, b;
        if (!(iss >> a >> b)) { break; } // error
        */
    } 
}
