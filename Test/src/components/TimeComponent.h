#pragma once
#include <string>

#include "Component.h"

namespace task_manager {
	class TimeComponent final : public Component
	{

	public:
		TimeComponent(uint32_t minutes = 0u, uint32_t hours = 0u);
		TimeComponent(const std::string& t);

		inline uint32_t GetMinutes() const noexcept { return m_Minutes; }
		void SetMinutes(uint32_t minutes);

		inline uint32_t GetHours() const noexcept { return m_Hours; }
		void SetHours(uint32_t hours);

		std::string GetString() const noexcept override;

		bool operator==(const Component& component) const noexcept override;
		bool operator!=(const Component& component) const noexcept override;
		bool operator< (const Component& component) const noexcept override;
		bool operator> (const Component& component) const noexcept override;
		bool operator<=(const Component& component) const noexcept override;
		bool operator>=(const Component& component) const noexcept override;

	private:
		void ThrowExceptionIfMinutesInvalid(uint32_t field) const;
		void ThrowExceptionIfHoursInvalid(uint32_t hours) const;

	private:
		uint32_t m_Minutes;
		uint32_t m_Hours;
	};
}