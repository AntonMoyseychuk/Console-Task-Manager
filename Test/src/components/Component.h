#pragma once
#include <string>

namespace task_manager {
	class Component
	{
	public:
		virtual std::string GetString() const noexcept = 0;

		virtual bool operator==(const Component& component) const noexcept = 0;
		virtual bool operator!=(const Component& component) const noexcept = 0;
		virtual bool operator<(const Component& component) const noexcept = 0;
		virtual bool operator>(const Component& component) const noexcept = 0;
		virtual bool operator<=(const Component& component) const noexcept = 0;
		virtual bool operator>=(const Component& component) const noexcept = 0;

	protected:
		template<typename T>
		bool IsFieldValid(const T& field, const T min, const T max) const noexcept
		{
			return field >= min && field <= max;
		}
	};
}