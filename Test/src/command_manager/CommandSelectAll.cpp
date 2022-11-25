#include "CommandSelectAll.h"

#include "task_manager/Task.h"

namespace command_manager {
	CommandSelectAll::CommandSelectAll(uint32_t code)
		: Command("select *", code)
	{

	}

	std::set<task_manager::Task> CommandSelectAll::Execute(const std::vector<std::string> args, 
		const std::set<task_manager::Task>& collection) const
	{
		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(!args.empty(), "[SYNTAX ERROR]: invalid \"select *\" command arguments count.\n"
			"The syntax: select *");

		return collection;
	}
}