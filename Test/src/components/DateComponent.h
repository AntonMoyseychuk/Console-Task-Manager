#pragma once
#include <string>
#include <array>

#include "TimeComponent.h"

namespace task_manager {
	class DateComponent final : public Component
	{
	private:
		enum Month { JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER };

	public:
		DateComponent(uint32_t day = 1u, uint32_t month = 1u, uint32_t year = 0u, uint32_t minute = 0, uint32_t hour = 0);
		DateComponent(const std::string& date);

		inline uint32_t GetDay() const noexcept { return m_Day; }
		void SetDay(uint32_t day);

		inline uint32_t GetMonth() const noexcept { return m_Month; }
		void SetMonth(uint32_t month);

		inline uint32_t GetYear() const noexcept { return m_Year; }
		void SetYear(uint32_t year);

		inline TimeComponent GetTime() const noexcept { return m_Time; }
		void SetTime(const TimeComponent& t);

		std::string GetString() const noexcept override;

		bool operator==(const Component& component) const noexcept override;
		bool operator!=(const Component& component) const noexcept override;
		bool operator< (const Component& component) const noexcept override;
		bool operator> (const Component& component) const noexcept override;
		bool operator<=(const Component& component) const noexcept override;
		bool operator>=(const Component& component) const noexcept override;

	private:
		void ThrowExceptionIfDayInvalid(uint32_t day, bool isYearLeap) const;
		void ThrowExceptionIfMonthInvalid(uint32_t month) const;

		bool IsLeapYear(uint32_t year) const noexcept;

	private:
		static constexpr std::array<uint16_t, DECEMBER> DAYS_IN_MONTHS = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		static const std::array<std::string, DECEMBER> MONTH_STRINGS;

	private:
		uint32_t m_Day;
		uint32_t m_Month;
		uint32_t m_Year;

		TimeComponent m_Time;

		bool m_IsLeapYear;
	};
}