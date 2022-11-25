#include <iostream>

#include "Task.h"


namespace task_manager {
	Task::Task()
		: m_Name(""), m_Date(), m_Description(""), m_Category(""), m_Status(false)
	{
	}

	Task::Task(const NameComponent& name, const DescriptionComponent& description, 
		const DateComponent& date, const CategoryComponent& category, StatusComponent status)
		: m_Name(name), m_Date(date), m_Description(description), m_Category(category), m_Status(status)
	{
	}

	void Task::SetName(const NameComponent& name)
	{
		m_Name = name;
	}

	void Task::SetDate(const DateComponent& date)
	{
		m_Date = date;
	}

	void Task::SetTime(const TimeComponent& time)
	{
		m_Date.SetTime(time);
	}

	void Task::SetDescription(const DescriptionComponent& description)
	{
		m_Description = description;
	}

	void Task::SetCategory(const CategoryComponent& category)
	{
		m_Category = category;
	}

	void Task::SetStatus(const StatusComponent& status)
	{
		m_Status = status;
	}

	NameComponent Task::GetName() const noexcept
	{
		return m_Name;
	}

	DateComponent Task::GetDate() const noexcept
	{
		return m_Date;
	}

	TimeComponent Task::GetTime() const noexcept
	{
		return m_Date.GetTime();
	}

	DescriptionComponent Task::GetDescription() const noexcept
	{
		return m_Description;
	}

	CategoryComponent Task::GetCategory() const noexcept
	{
		return m_Category;
	}

	StatusComponent Task::GetStatus() const noexcept
	{
		return m_Status;
	}

	bool Task::operator<(const Task& task) const noexcept
	{
		return m_Name < task.m_Name;
	}

	bool Task::operator>(const Task& task) const noexcept
	{
		return m_Name > task.m_Name;
	}

	std::ostream& operator<<(std::ostream& os, const Task& task)
	{
		os << "[NAME]:" << task.GetName().GetString() << ' '
			<< "[DESC]:" << task.GetDescription().GetString() << ' '
			<< "[DATE]:" << task.GetDate().GetString() << ' '
			<< task.GetTime().GetString() << ' '
			<< "[CATEGORY]:" << task.GetCategory().GetString() << ' '
			<< "[STATUS]:" << task.GetStatus().GetString();
		return os;
	}
}