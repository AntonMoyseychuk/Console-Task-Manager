#include "CommandDelete.h"

#include "task_manager/Task.h"

namespace command_manager {
	CommandDelete::CommandDelete(uint32_t code)
		: Command("delete", code)
	{
	}

	std::set<task_manager::Task> CommandDelete::Execute(const std::vector<std::string> args, const std::set<task_manager::Task>& collection) const
	{
		using namespace task_manager;

		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(args.size() != 1, "[SYNTAX ERROR]: invalid \"delete\" command arguments count.\n"
			"The syntax: delete [NAME]");

		auto result = collection;

		Task task(NameComponent(args[0]), DescriptionComponent(""), DateComponent("0000-01-01 00:00"), "");
		auto it = _SearchTask(task.GetName().GetString(), result);

		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(it == result.end(),
			"[SEARCH ERROR]: there is no \"" + task.GetName().GetString() + "\" task.");

		result.erase(it);

		return result;
	}
}