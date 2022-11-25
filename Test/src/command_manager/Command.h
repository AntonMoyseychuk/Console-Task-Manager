#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <set>


#define THROW_INVALID_ARG_EXCEPTION_IF_TRUE(expr, msg) if ((expr)) throw std::invalid_argument(msg)


namespace task_manager {
	class Task;
}

namespace command_manager {
	class Command
	{
	public:
		Command(const std::string& strVersion, uint32_t code);
		std::string GetStrVersion() const noexcept;
		uint32_t GetCommandCode() const noexcept;
		
		virtual std::set<task_manager::Task> Execute(const std::vector<std::string> args, 
			const std::set<task_manager::Task>& collection) const = 0;
		
		bool operator<(const Command& command) const noexcept;
		bool operator>(const Command& command) const noexcept;
		bool operator==(const Command& command) const noexcept;
		bool operator!=(const Command& command) const noexcept;

	protected:
		static std::set<task_manager::Task>::iterator _SearchTask(const std::string& name,
			const std::set<task_manager::Task>& collection);

	private:
		std::string m_StringVersion;
		uint32_t m_Code;
	};
}