#pragma once
#include <set>

#include "command_manager/CommandManager.h"

namespace task_manager {
	class TaskManager final
	{
	public:
		static TaskManager& Get() noexcept;

		std::set<Task> Execute(const std::string& command);

	private:
		TaskManager();

	private:
		enum ECommand { ADD, DONE, UPDATE, DELETE, SELECT_ALL, SELECT_ALL_WHERE, EXIT };

	private:
		static command_manager::CommandManager m_CommandManager;

	private:
		std::set<Task> m_Tasks;
	};
}