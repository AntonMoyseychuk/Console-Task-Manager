#pragma once
#include "components/DateComponent.h"
#include "components/TimeComponent.h"
#include "components/StatusComponent.h"
#include "components/NameComponent.h"
#include "components/DescriptionComponent.h"
#include "components/CategoryComponent.h"

namespace task_manager {
	class Task
	{
	public:
		Task();
		Task(const NameComponent& name, const DescriptionComponent& description, const DateComponent& date,
			const CategoryComponent& category, StatusComponent status = StatusComponent(false));

		void SetName(const NameComponent& name);
		void SetDate(const DateComponent& date);
		void SetTime(const TimeComponent& time);
		void SetDescription(const DescriptionComponent& description);
		void SetCategory(const CategoryComponent& category);
		void SetStatus(const StatusComponent& status);

		NameComponent GetName() const noexcept;
		DateComponent GetDate() const noexcept;
		TimeComponent GetTime() const noexcept;
		DescriptionComponent GetDescription() const noexcept;
		CategoryComponent GetCategory() const noexcept;
		StatusComponent GetStatus() const noexcept;

		bool operator<(const Task& task) const noexcept;
		bool operator>(const Task& task) const noexcept;

		friend std::ostream& operator<<(std::ostream& os, const Task& task);

	private:
		NameComponent m_Name;
		DateComponent m_Date;
		DescriptionComponent m_Description;
		CategoryComponent m_Category;
		StatusComponent m_Status;
	};
}