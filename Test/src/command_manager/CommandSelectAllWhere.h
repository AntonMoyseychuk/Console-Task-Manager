#pragma once
#include <map>

#include "Command.h"

namespace task_manager {
	class Component;
}

namespace command_manager {
	class CommandSelectAllWhere final : public Command
	{
	public:
		CommandSelectAllWhere(uint32_t code);

		std::set<task_manager::Task> Execute(const std::vector<std::string> predicate,
			const std::set<task_manager::Task>& collection) const override;

	private:
		enum KeyField { NAME, DATE, CATEGORY, STATUS, DESCRIPTION };
		static const std::map<std::string, std::pair<std::string, CommandSelectAllWhere::KeyField>> KEY_FIELDS;

		enum Operator { LIKE, LESS, LESS_OR_EQUAL, EQUAL, GREATER_OR_EQUAL, GREATER };
		static const std::map<std::string, std::pair<std::string, CommandSelectAllWhere::Operator>> OPERATORS;

		enum KeyWord { AND };
		static const std::map<std::string, std::pair<std::string, CommandSelectAllWhere::KeyWord>> KEY_WORDS;

	private:
		static std::set<task_manager::Task> _SelectTasksWithExpression(KeyField field, Operator op, 
			const task_manager::Component* value, const std::set<task_manager::Task>& preSelection);

		static std::set<task_manager::Task> __SelectTasksWithNameParameter(Operator op, 
			const task_manager::Component* value, const std::set<task_manager::Task>& preSelection);
		
		static std::set<task_manager::Task> __SelectTasksWithDateParameter(Operator op, 
			const task_manager::Component* value, const std::set<task_manager::Task>& preSelection);
		
		static std::set<task_manager::Task> __SelectTasksWithCategoryParameter(Operator op, 
			const task_manager::Component* value, const std::set<task_manager::Task>& preSelection);
		
		static std::set<task_manager::Task> __SelectTasksWithStatusParameter(Operator op, 
			const task_manager::Component* value, const std::set<task_manager::Task>& preSelection);
		
		static std::set<task_manager::Task> __SelectTasksWithDescriptionParameter(Operator op,
			const task_manager::Component* value, const std::set<task_manager::Task>& preSelection);
	};
}