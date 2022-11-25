#pragma once
#include <map>
#include <string>
#include <memory>

#include "CommandAdd.h"
#include "CommandDelete.h"
#include "CommandDone.h"
#include "CommandExit.h"
#include "CommandSelectAll.h"
#include "CommandSelectAllWhere.h"
#include "CommandUpdate.h"

#include "task_manager/Task.h"

namespace command_manager {
	class CommandManager final
	{
	public:
		static CommandManager& Get() noexcept;

		void AddCommand(std::shared_ptr<Command> command);

		std::set<task_manager::Task> Execute(uint32_t command, const std::vector<std::string> args, 
			const std::set<task_manager::Task>& collection);

		std::map<std::string, std::shared_ptr<Command>> GetCommandsStrings() const noexcept;

	private:
		CommandManager() = default;

	private:
		std::map<uint32_t, std::shared_ptr<Command>> m_Commands;
	};
}