#include <iostream>
#include "task_manager/TaskManager.h"
#include "command_manager/StringParser.h"

int main()
{
	task_manager::TaskManager manager = task_manager::TaskManager::Get();
	std::string command;
	
	try {
		while (true) {
			try {
				std::cout << ":> ";
				std::getline(std::cin, command);
				const auto result = manager.Execute(command);
				for (const auto& task : result) {
					std::cout << task << '\n';
				}
				std::cout << std::endl;
			}
			catch (const std::exception& ex) {
				std::cout << ex.what() << "\n\n";
			}
		}
	}
	catch (const int& exitCode) {
		return exitCode;
	}

	return 0;
}