#pragma once
#include "Command.h"

namespace command_manager {
	class CommandAdd final : public Command
	{
	public:
		CommandAdd(uint32_t code);
		
		std::set<task_manager::Task> Execute(const std::vector<std::string> args, 
			const std::set<task_manager::Task>& collection) const override;
	};
}