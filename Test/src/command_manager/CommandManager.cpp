#include <stdexcept>
#include "CommandManager.h"

#define THROW_INVALID_ARG_EXCEPTION_IF_TRUE(expr, msg) if ((expr))	throw std::invalid_argument(msg)

namespace command_manager {
	CommandManager& CommandManager::Get() noexcept
	{
		static CommandManager manager;
		return manager;
	}

	void CommandManager::AddCommand(std::shared_ptr<Command> command)
	{
		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(m_Commands.find(command->GetCommandCode()) != m_Commands.end(),
			"[COMMAND MANAGER ERROR]: command \"" + command->GetStrVersion() + "\" already exists.");
		
		m_Commands.insert(std::make_pair(command->GetCommandCode(), std::move(command)));
	}

	std::set<task_manager::Task> CommandManager::Execute(uint32_t command, const std::vector<std::string> args, 
		const std::set<task_manager::Task>& collection)
	{
		std::map<uint32_t, std::shared_ptr<Command>>::iterator it;
		THROW_INVALID_ARG_EXCEPTION_IF_TRUE((it = m_Commands.find(command)) == m_Commands.end(),
			"[COMMAND MANAGER ERROR]: there is no command with such code \"" + std::to_string(command) + "\".");

		return it->second->Execute(args, collection);
	}

	std::map<std::string, std::shared_ptr<Command>> CommandManager::GetCommandsStrings() const noexcept
	{
		std::map<std::string, std::shared_ptr<Command>> result;

		for (const auto& command : m_Commands) {
			result.insert(std::make_pair(command.second->GetStrVersion(), command.second));
		}

		return result;
	}
}