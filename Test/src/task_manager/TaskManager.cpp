#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <memory>

#include "TaskManager.h"
#include "command_manager/StringParser.h"

#define THROW_INVALID_ARG_EXCEPTION_IF_TRUE(expr, msg) if ((expr))	throw std::invalid_argument(msg)


namespace task_manager {
	command_manager::CommandManager TaskManager::m_CommandManager = command_manager::CommandManager::Get();

	TaskManager& TaskManager::Get() noexcept
	{
		static TaskManager taskManager;
		return taskManager;
	}

	std::set<Task> TaskManager::Execute(const std::string& command)
	{
		using namespace string_utility;
		
		auto tokens = StringParser::Split(command);
		if (tokens.empty()) {
			return std::set<Task>();
		}

		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(tokens.size() == 1 && StringParser::ToLowerCase(tokens[0]) != "exit",
			"[SYNTAX ERROR]: invalid command \"" + tokens[0] + "\".");
		
		tokens[0] = StringParser::ToLowerCase(tokens[0]);
		if (tokens[0] == "select") {
			const uint32_t SELECT_ALL_SIZE = 2u;
			const uint32_t SELECT_ALL_WHERE_MIN_SIZE = 3u;

			if (tokens.size() == SELECT_ALL_SIZE && tokens[SELECT_ALL_SIZE - 1] == "*") {
				tokens[0] += " *";
				tokens.resize(1);
			}
			else if (tokens.size() >= SELECT_ALL_WHERE_MIN_SIZE && tokens[SELECT_ALL_WHERE_MIN_SIZE - 2u] == "*" 
				&& StringParser::ToLowerCase(tokens[SELECT_ALL_WHERE_MIN_SIZE - 1u]) == "where") 
			{
				tokens[0] += " * where";
				tokens.erase(tokens.begin() + 1, tokens.begin() + SELECT_ALL_WHERE_MIN_SIZE);
			}
			else {
				for (auto token = tokens.begin() + 1; token < tokens.end(); ++token) {
					tokens[0] += " " + (*token);
				}
				THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: invalid command \"" + tokens[0] + "\".");
			}
		}

		auto commands = m_CommandManager.GetCommandsStrings();
		auto it = commands.find(tokens[0]);
		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(it == commands.end(), "[SYNTAX ERROR]: invalid command \"" + tokens[0] + "\".");

		const auto args = std::vector<std::string>(tokens.begin() + 1, tokens.end());

		if (it->second->GetCommandCode() == SELECT_ALL || it->second->GetCommandCode() == SELECT_ALL_WHERE) {
			return m_CommandManager.Execute(it->second->GetCommandCode(), args, m_Tasks);
		}
		else {
			m_Tasks = m_CommandManager.Execute(it->second->GetCommandCode(), args, m_Tasks);
		}

		return m_Tasks;
	}

	TaskManager::TaskManager()
	{
		using namespace command_manager;

		m_CommandManager.AddCommand(std::make_shared<CommandAdd>(ADD));
		m_CommandManager.AddCommand(std::make_shared<CommandDelete>(DELETE));
		m_CommandManager.AddCommand(std::make_shared<CommandDone>(DONE));
		m_CommandManager.AddCommand(std::make_shared<CommandExit>(EXIT));
		m_CommandManager.AddCommand(std::make_shared<CommandSelectAll>(SELECT_ALL));
		m_CommandManager.AddCommand(std::make_shared<CommandSelectAllWhere>(SELECT_ALL_WHERE));
		m_CommandManager.AddCommand(std::make_shared<CommandUpdate>(UPDATE));
	}
}