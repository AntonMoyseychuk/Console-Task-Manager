#include "Command.h"

#include "task_manager/Task.h"

namespace command_manager {
	Command::Command(const std::string& strVersion, uint32_t code)
		: m_StringVersion(strVersion), m_Code(code)
	{
	}

	std::string Command::GetStrVersion() const noexcept
	{
		return m_StringVersion;
	}

	uint32_t Command::GetCommandCode() const noexcept
	{
		return m_Code;
	}

	bool Command::operator<(const Command& command) const noexcept
	{
		return m_StringVersion < command.m_StringVersion;
	}

	bool Command::operator>(const Command& command) const noexcept
	{
		return !(*this < command || *this == command);
	}

	bool Command::operator==(const Command& command) const noexcept
	{
		return m_StringVersion == command.m_StringVersion;
	}

	bool Command::operator!=(const Command& command) const noexcept
	{
		return !(*this == command);
	}

	std::set<task_manager::Task>::iterator Command::_SearchTask(const std::string& name, const std::set<task_manager::Task>& collection)
	{
		return std::find_if(collection.begin(), collection.end(), [&name](const task_manager::Task& t) {
			return t.GetName().GetString() == name;
		});
	}
}