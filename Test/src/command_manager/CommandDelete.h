#pragma once
#include "Command.h"

namespace command_manager {
	class CommandDelete final : public Command
	{
	public:
		CommandDelete(uint32_t code);

		std::set<task_manager::Task> Execute(const std::vector<std::string> args,
			const std::set<task_manager::Task>& collection) const override;
	};
}

