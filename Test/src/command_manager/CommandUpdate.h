#pragma once
#include "Command.h"

namespace command_manager {
	class CommandUpdate final : public Command
	{
	public:
		CommandUpdate(uint32_t code);

		std::set<task_manager::Task> Execute(const std::vector<std::string> args,
			const std::set<task_manager::Task>& collection) const override;
	};
}