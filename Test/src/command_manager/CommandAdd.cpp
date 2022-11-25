#include "CommandAdd.h"

#include "task_manager/Task.h"

namespace command_manager {
	CommandAdd::CommandAdd(uint32_t code)
		: Command("add", code)
	{
	}

	std::set<task_manager::Task> CommandAdd::Execute(const std::vector<std::string> args, const std::set<task_manager::Task>& collection) const
	{
		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(args.size() != 4, "[SYNTAX ERROR]: invalid \"add\" command arguments count.\n"
			"The syntax: add [NAME] [DESCRIPTION] [DATE {yyyy-mm-dd hh:mm}] [CATEGORY]");

		auto result = collection;

		task_manager::Task task(args[0], args[1], args[2], args[3]);
		auto it = _SearchTask(task.GetName().GetString(), result);

		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(it != result.end(),
			"[SEARCH ERROR]: \"" + task.GetName().GetString() + "\" task already exists.");

		result.insert(task);
		return result;
	}
}