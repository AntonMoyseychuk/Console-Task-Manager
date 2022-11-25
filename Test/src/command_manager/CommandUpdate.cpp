#include "CommandUpdate.h"

#include "task_manager/Task.h"

namespace command_manager {
	CommandUpdate::CommandUpdate(uint32_t code)
		: Command("update", code)
	{
	}

	std::set<task_manager::Task> CommandUpdate::Execute(const std::vector<std::string> args, const std::set<task_manager::Task>& collection) const
	{
		using namespace task_manager;

		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(args.size() != 5, "[SYNTAX ERROR]: invalid \"update\" command arguments count.\n"
			"The syntax: upadte [OLD_NAME] [NEW_NAME] [NEW_DESCRIPTION] [NEW_DATE {yyyy-mm-dd hh:mm}] [NEW_CATEGORY]");

		auto result = collection;

		Task task(NameComponent(args[0]), DescriptionComponent(""), DateComponent("0000-01-01 00:00"), "");
		auto it = _SearchTask(task.GetName().GetString(), result);

		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(it == result.end(),
			"[SEARCH ERROR]: there is no \"" + task.GetName().GetString() + "\" task.");

		task.SetName(args[1]);
		task.SetDescription(args[2]);
		task.SetDate(args[3]);
		task.SetCategory(args[4]);
		task.SetStatus("on");

		result.erase(it);
		result.insert(task);

		return result;
	}
}