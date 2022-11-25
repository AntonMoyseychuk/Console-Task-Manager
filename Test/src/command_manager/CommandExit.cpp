#include "CommandExit.h"

#include "task_manager/Task.h"

#define THROW_EXIT_EXCEPTION() throw 0;

namespace command_manager {
	CommandExit::CommandExit(uint32_t code)
		: Command("exit", code)
	{
	}

	std::set<task_manager::Task> CommandExit::Execute(const std::vector<std::string> args, 
		const std::set<task_manager::Task>& collection) const
	{
		THROW_EXIT_EXCEPTION();
		return std::set<task_manager::Task>();
	}
}