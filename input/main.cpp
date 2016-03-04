// raleigh-triangle-index.cpp : Defines the entry point for the console application.
//

#include "input.h"
#include "processing.h"
#include "output.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

#include <windows.h>

int main(int argc, char **argv)
{
	input triangle = input();
    SYSTEMTIME time;
	
	while (true) {
		// get current system time

		GetSystemTime(&time);
		// initialize our input class

		try {
			triangle.run(argc, argv);
		}
		catch (Exception &e) {
			std::cerr << "Library Exception!!! " << e.description() << std::endl;
		}

		std::vector<t_securitydata> maindata;
		maindata = triangle.data;

		processing RTA(triangle.data);
		std::cout	<< time.wHour << ":"
					<< time.wMinute << ":"
					<< time.wSecond << ":"
					<< time.wMilliseconds << " the index value is "
					<< RTA.calculateindex() 
					<< std::endl;

		Sleep(1000);
	}

	// wait for enter key to exit application
	std::cout << "Press ENTER to quit" << std::endl;
	std::cin.get();
	
	return 0;
}
