#pragma once
#include "Command.h"

namespace command_manager {
	class CommandSelectAll final : public Command
	{
	public:
		CommandSelectAll(uint32_t code);

		std::set<task_manager::Task> Execute(const std::vector<std::string> args,
			const std::set<task_manager::Task>& collection) const override;
	};
}