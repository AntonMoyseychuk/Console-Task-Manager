#include <memory>

#include "CommandSelectAllWhere.h"
#include "StringParser.h"
#include "task_manager/Task.h"

namespace command_manager {
	const std::map<std::string, std::pair<std::string, CommandSelectAllWhere::KeyWord>> CommandSelectAllWhere::KEY_WORDS = {
		{ "and",			std::make_pair("and", CommandSelectAllWhere::KeyWord::AND) },
	};

	const std::map<std::string, std::pair<std::string, CommandSelectAllWhere::KeyField>> CommandSelectAllWhere::KEY_FIELDS = {
		{ "date",			std::make_pair("date", CommandSelectAllWhere::KeyField::DATE) },
		{ "name",			std::make_pair("name", CommandSelectAllWhere::KeyField::NAME) },
		{ "description",	std::make_pair("description", CommandSelectAllWhere::KeyField::DESCRIPTION) },
		{ "category",		std::make_pair("category", CommandSelectAllWhere::KeyField::CATEGORY) },
		{ "status",			std::make_pair("status", CommandSelectAllWhere::KeyField::STATUS) },
	};

	const std::map<std::string, std::pair<std::string, CommandSelectAllWhere::Operator>> CommandSelectAllWhere::OPERATORS = {
		{ "like",	std::make_pair("like", CommandSelectAllWhere::Operator::LIKE) },

		{ "<",		std::make_pair("<", CommandSelectAllWhere::Operator::LESS) },
		{ "<=",		std::make_pair("<=", CommandSelectAllWhere::Operator::LESS_OR_EQUAL) },
		{ "=",		std::make_pair("=", CommandSelectAllWhere::Operator::EQUAL) },
		{ ">=",		std::make_pair(">=", CommandSelectAllWhere::Operator::GREATER_OR_EQUAL) },
		{ ">",		std::make_pair(">", CommandSelectAllWhere::Operator::GREATER) },
	};

	CommandSelectAllWhere::CommandSelectAllWhere(uint32_t code)
		: Command("select * where", code)
	{

	}

	std::set<task_manager::Task> CommandSelectAllWhere::Execute(const std::vector<std::string> predicate, 
		const std::set<task_manager::Task>& collection) const
	{
		using namespace task_manager;
		using namespace string_utility;

		auto result = collection;

		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(predicate.size() < 3, "[SYNTAX ERROR]: to few parameters in the \"select * where\" command.");

		// f - field, op - operator, kw - key word
		// 
		// 
		//            f   op       value        kw
		//predicate: date < "2020-12-12 00:00" and status =  "on" and description like "text"
		//           |      expression       |     | expression |     |     expression      |

		static const uint8_t EXPRESSION_SIZE = 3;

		for (uint32_t i = 0; i < predicate.size(); ) {
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(i + 2 >= predicate.size(),
				"[SYNTAX ERROR]: an argument in the \"select * where\" command was omitted.");

			const auto field = KEY_FIELDS.find(StringParser::ToLowerCase(predicate[i]));
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(field == KEY_FIELDS.end(),
				"[SYNTAX ERROR]: there is no such field \"" + predicate[i] + "\".");

			const auto op = OPERATORS.find(StringParser::ToLowerCase(predicate[i + 1]));
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(op == OPERATORS.end(),
				"[SYNTAX ERROR]: there is no such field \"" + predicate[i + 1] + "\".");

			std::unique_ptr<Component> value = nullptr;
			switch (field->second.second)
			{
			case NAME:
				value = std::make_unique<NameComponent>(predicate[i + 2]);
				break;
			case DATE:
				value = std::make_unique<DateComponent>(predicate[i + 2]);
				break;

			case CATEGORY:
				value = std::make_unique<CategoryComponent>(predicate[i + 2]);
				break;

			case STATUS:
				value = std::make_unique<StatusComponent>(predicate[i + 2]);
				break;

			case DESCRIPTION:
				value = std::make_unique<DescriptionComponent>(predicate[i + 2]);
				break;
			}

			result = _SelectTasksWithExpression(field->second.second, op->second.second, value.get(), result);

			i += EXPRESSION_SIZE;
			if (i + 1 < predicate.size() && KEY_WORDS.find(StringParser::ToLowerCase(predicate[i])) != KEY_WORDS.end()) {
				++i;
			}
		}

		return result;
	}
	
	std::set<task_manager::Task> CommandSelectAllWhere::_SelectTasksWithExpression(KeyField field, Operator op, 
		const task_manager::Component* value, const std::set<task_manager::Task>& preSelection)
	{
		switch (field)
		{
		case NAME:
			return __SelectTasksWithNameParameter(op, value, preSelection);

		case DATE:
			return __SelectTasksWithDateParameter(op, value, preSelection);

		case CATEGORY:
			return __SelectTasksWithCategoryParameter(op, value, preSelection);

		case STATUS:
			return __SelectTasksWithStatusParameter(op, value, preSelection);

		case DESCRIPTION:
			return __SelectTasksWithDescriptionParameter(op, value, preSelection);
		}
	}
	
	std::set<task_manager::Task> CommandSelectAllWhere::__SelectTasksWithNameParameter(Operator op, 
		const task_manager::Component* value, const std::set<task_manager::Task>& preSelection)
	{
		std::set<task_manager::Task> result;

		switch (op)
		{
		case LIKE:
			for (const auto& task : preSelection) {
				if (task.GetName().GetString().find(value->GetString()) != std::string::npos) {
					result.insert(task);
				}
			}
			break;
		case LESS:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \"<\" can't be used with field \"name\"");
			break;
		case LESS_OR_EQUAL:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \"<=\" can't be used with field \"name\"");
			break;
		case EQUAL:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \"=\" can't be used with field \"name\", use select *");
			break;
		case GREATER_OR_EQUAL:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \">=\" can't be used with field \"name\"");
			break;
		case GREATER:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \">\" can't be used with field \"name\"");
			break;
		}

		return result;
	}
	
	std::set<task_manager::Task> CommandSelectAllWhere::__SelectTasksWithDateParameter(Operator op, 
		const task_manager::Component* value, const std::set<task_manager::Task>& preSelection)
	{
		std::set<task_manager::Task> result;

		switch (op)
		{
		case LIKE:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \"like\" can't be used with field \"date\"");
			break;
		case LESS:
			for (const auto& task : preSelection) {
				if (task.GetDate() < (*value)) {
					result.insert(task);
				}
			}
			break;
		case LESS_OR_EQUAL:
			for (const auto& task : preSelection) {
				if (task.GetDate() <= (*value)) {
					result.insert(task);
				}
			}
			break;
		case EQUAL:
			for (const auto& task : preSelection) {
				if (task.GetDate() == (*value)) {
					result.insert(task);
				}
			}
			break;
		case GREATER_OR_EQUAL:
			for (const auto& task : preSelection) {
				if (task.GetDate() >= (*value)) {
					result.insert(task);
				}
			}
			break;
		case GREATER:
			for (const auto& task : preSelection) {
				if (task.GetDate() > (*value)) {
					result.insert(task);
				}
			}
			break;
		}

		return result;
	}
	
	std::set<task_manager::Task> CommandSelectAllWhere::__SelectTasksWithCategoryParameter(Operator op, 
		const task_manager::Component* value, const std::set<task_manager::Task>& preSelection)
	{
		std::set<task_manager::Task> result;

		switch (op)
		{
		case LIKE:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \"like\" can't be used with field \"category\"");
			break;
		case LESS:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \"<\" can't be used with field \"category\"");
			break;
		case LESS_OR_EQUAL:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \"<=\" can't be used with field \"category\"");
			break;
		case EQUAL:
			for (const auto& task : preSelection) {
				if (task.GetCategory() == (*value)) {
					result.insert(task);
				}
			}
			break;
		case GREATER_OR_EQUAL:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \">=\" can't be used with field \"category\"");
			break;
		case GREATER:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \">\" can't be used with field \"category\"");
			break;
		}

		return result;
	}
	
	std::set<task_manager::Task> CommandSelectAllWhere::__SelectTasksWithStatusParameter(Operator op, 
		const task_manager::Component* value, const std::set<task_manager::Task>& preSelection)
	{
		std::set<task_manager::Task> result;

		switch (op)
		{
		case LIKE:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \"like\" can't be used with field \"status\"");
			break;
		case LESS:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \"<\" can't be used with field \"status\"");
			break;
		case LESS_OR_EQUAL:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \"<=\" can't be used with field \"status\"");
			break;
		case EQUAL:
			for (const auto& task : preSelection) {
				if (task.GetStatus() == (*value)) {
					result.insert(task);
				}
			}
			break;
		case GREATER_OR_EQUAL:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \">=\" can't be used with field \"status\"");
			break;
		case GREATER:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \">\" can't be used with field \"status\"");
			break;
		}

		return result;
	}

	std::set<task_manager::Task> CommandSelectAllWhere::__SelectTasksWithDescriptionParameter(Operator op, 
		const task_manager::Component* value, const std::set<task_manager::Task>& preSelection)
	{
		std::set<task_manager::Task> result;

		switch (op)
		{
		case LIKE:
			for (const auto& task : preSelection) {
				if (task.GetDescription().GetString().find(value->GetString()) != std::string::npos) {
					result.insert(task);
				}
			}
			break;
		case LESS:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \"<\" can't be used with field \"description\"");
			break;
		case LESS_OR_EQUAL:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \"<=\" can't be used with field \"description\"");
			break;
		case EQUAL:
			for (const auto& task : preSelection) {
				if (task.GetDescription() == (*value)) {
					result.insert(task);
				}
			}
			break;
		case GREATER_OR_EQUAL:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \">=\" can't be used with field \"description\"");
			break;
		case GREATER:
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[SYNTAX ERROR]: the opperator \">\" can't be used with field \"description\"");
			break;
		}

		return result;
	}
}