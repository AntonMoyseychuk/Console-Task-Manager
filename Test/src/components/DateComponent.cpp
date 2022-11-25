#include <stdexcept>
#include <sstream>

#include "command_manager/StringParser.h"
#include "DateComponent.h"

#define THROW_INVALID_ARG_EXCEPTION_IF_TRUE(expr, msg) if ((expr))	throw std::invalid_argument(msg)

namespace task_manager {
	const inline std::array<std::string, DateComponent::Month::DECEMBER> DateComponent::MONTH_STRINGS = {
		"JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"
	};

	DateComponent::DateComponent(uint32_t day, uint32_t month, uint32_t year, uint32_t minute, uint32_t hour)
		: m_Day(day), m_Month(month), m_Year(year), m_Time(minute, hour)
	{
		ThrowExceptionIfMonthInvalid(m_Month);

		m_IsLeapYear = IsLeapYear(year);

		ThrowExceptionIfDayInvalid(m_Day, m_IsLeapYear);
	}

	DateComponent::DateComponent(const std::string& date)
	{
		const auto components = string_utility::StringParser::Split(date, ' ');
		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(components.size() != 2, "[INVALID ARGUMENT]: the syntax of date is {yyyy-mm-dd hh:mm}.");

		const auto d = string_utility::StringParser::Split(components[0], '-');
		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(d.size() != 3, "[INVALID ARGUMENT]: the syntax of date is {yyyy-mm-dd hh:mm}.");

		const auto t = string_utility::StringParser::Split(components[1], ':');
		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(t.size() != 2, "[INVALID ARGUMENT]: the syntax of date is {yyyy-mm-dd hh:mm}.");
		std::stringstream sd(d[2] + " " + d[1] + " " + d[0]);
		
		uint32_t year, month, day;
		sd >> day >> month >> year;

		SetYear(year);
		SetMonth(month);
		SetDay(day);

		std::stringstream st(t[1] + " " + t[0]);
		
		uint32_t minute, hour;
		st >> minute >> hour;
		m_Time.SetMinutes(minute);
		m_Time.SetHours(hour);
	}

	void DateComponent::SetDay(uint32_t day)
	{
		ThrowExceptionIfDayInvalid(day, m_IsLeapYear);
		m_Day = day;
	}

	void DateComponent::SetMonth(uint32_t month)
	{
		ThrowExceptionIfMonthInvalid(month);
		m_Month = month;
	}

	void DateComponent::SetYear(uint32_t year)
	{
		m_IsLeapYear = IsLeapYear(year);
		m_Year = year;
	}

	void DateComponent::SetTime(const TimeComponent& t)
	{
		m_Time = t;
	}

	std::string DateComponent::GetString() const noexcept
	{
		return std::to_string(m_Year) 
			+ "-" + (m_Month < 10 ? "0" : "") + std::to_string(m_Month) 
			+ "-" + (m_Day   < 10 ? "0" : "") + std::to_string(m_Day);
	}

	bool DateComponent::operator==(const Component& component) const noexcept
	{
		if (const auto date = dynamic_cast<const DateComponent*>(&component)) {
			return m_Day == date->m_Day && m_Month == date->m_Month && m_Year == date->m_Year && m_Time == date->m_Time;
		}
		return false;
	}

	bool DateComponent::operator!=(const Component& component) const noexcept
	{
		return !(*this == component);
	}

	bool DateComponent::operator<(const Component& component) const noexcept
	{
		if (const auto date = dynamic_cast<const DateComponent*>(&component)) {
			if (m_Year < date->m_Year) {
				return true;
			}
			else if (m_Year > date->m_Year) {
				return false;
			}
			else if (m_Month < date->m_Month) {
				return true;
			}
			else if (m_Month > date->m_Month) {
				return false;
			}
			else if (m_Day < date->m_Day) {
				return true;
			}
			else {
				return m_Time < date->m_Time;
			}
		}
		return false;
	}

	bool DateComponent::operator>(const Component& component) const noexcept
	{
		return !(*this < component || *this == component);
	}

	bool DateComponent::operator<=(const Component& component) const noexcept
	{
		return (*this < component || *this == component);
	}

	bool DateComponent::operator>=(const Component& component) const noexcept
	{
		return !(*this < component);
	}

	void DateComponent::ThrowExceptionIfDayInvalid(uint32_t day, bool isYearLeap) const
	{
		if (isYearLeap && m_Month == FEBRUARY) {
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(!IsFieldValid(day, static_cast<uint32_t>(1u), static_cast<uint32_t>(29u)),
				"[INVALID ARGUMENT]: days in FEBRUARY must be between 1 and 29.");
		}
		else {
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(
				!IsFieldValid(day, static_cast<uint32_t>(1u), static_cast<uint32_t>(DAYS_IN_MONTHS[m_Month - 1])),
				"[INVALID ARGUMENT]: days in " + MONTH_STRINGS[m_Month - 1]
				+ " must be between 1 and " + std::to_string(DAYS_IN_MONTHS[m_Month - 1]) + "."
			);
		}
	}

	void DateComponent::ThrowExceptionIfMonthInvalid(uint32_t month) const
	{
		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(!IsFieldValid(month, static_cast<uint32_t>(JANUARY), static_cast<uint32_t>(DECEMBER)),
			"[INVALID ARGUMENT]: month must be between 1 and 12.");
	}

	bool DateComponent::IsLeapYear(uint32_t year) const noexcept
	{
		return ((year % 100 == 0 && year % 400 == 0) || year % 4 == 0);
	}
}