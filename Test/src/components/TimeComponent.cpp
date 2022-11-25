#include <stdexcept>
#include <sstream>

#include "command_manager/StringParser.h"
#include "TimeComponent.h"

#define THROW_INVALID_ARG_EXCEPTION_IF_TRUE(expr, msg) if ((expr))	throw std::invalid_argument(msg)

namespace task_manager {
	TimeComponent::TimeComponent(uint32_t minutes, uint32_t hours)
		: m_Minutes(minutes), m_Hours(hours)
	{
		ThrowExceptionIfMinutesInvalid(m_Minutes);
		ThrowExceptionIfHoursInvalid(m_Hours);
	}

	TimeComponent::TimeComponent(const std::string& t)
	{
		const auto components = string_utility::StringParser::Split(t, ':');
		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(components.size() != 2, "[INVALID ARGUMENT]: the syntax of time is {hh:mm}.");
		std::stringstream ss(components[1] + " " + components[0]);

		uint32_t hour, minute;
		ss >> minute >> hour;

		SetHours(hour);
		SetMinutes(minute);
	}

	void TimeComponent::SetMinutes(uint32_t minutes)
	{
		ThrowExceptionIfMinutesInvalid(minutes);
		m_Minutes = minutes;
	}

	void TimeComponent::SetHours(uint32_t hours)
	{
		ThrowExceptionIfHoursInvalid(hours);
		m_Hours = hours;
	}

	std::string TimeComponent::GetString() const noexcept
	{
		return (m_Hours < 10 ? "0" : "") + std::to_string(m_Hours) + ":" + (m_Minutes < 10 ? "0" : "") + std::to_string(m_Minutes);
	}

	bool TimeComponent::operator==(const Component& component) const noexcept
	{
		if (const auto t = dynamic_cast<const TimeComponent*>(&component)) {
			return m_Hours == t->m_Hours && m_Minutes == t->m_Minutes;
		}
		return false;
	}

	bool TimeComponent::operator!=(const Component& component) const noexcept
	{
		return !(*this == component);
	}

	bool TimeComponent::operator<(const Component& component) const noexcept
	{
		if (const auto t = dynamic_cast<const TimeComponent*>(&component)) {
			if (m_Hours < t->m_Hours) {
				return true;
			}
			else if (m_Hours > t->m_Hours) {
				return false;
			}
			else if (m_Minutes < t->m_Minutes) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}

	bool TimeComponent::operator>(const Component& component) const noexcept
	{
		return false;
	}

	bool TimeComponent::operator<=(const Component& component) const noexcept
	{
		return false;
	}

	bool TimeComponent::operator>=(const Component& component) const noexcept
	{
		return false;
	}

	void TimeComponent::ThrowExceptionIfMinutesInvalid(uint32_t minutes) const
	{
		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(!IsFieldValid(minutes, static_cast<uint32_t>(0u), static_cast<uint32_t>(59u)),
			"[INVALID ARGUMENT]: minutes must be between 0 and 59.");
	}

	void TimeComponent::ThrowExceptionIfHoursInvalid(uint32_t hours) const
	{
		THROW_INVALID_ARG_EXCEPTION_IF_TRUE(!IsFieldValid(hours, static_cast<uint32_t>(0u), static_cast<uint32_t>(23u)),
			"[INVALID ARGUMENT]: hours must be between 0 and 23.");
	}
}