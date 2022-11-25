#include <stdexcept>

#include "StatusComponent.h"

#define THROW_INVALID_ARG_EXCEPTION_IF_TRUE(expr, msg) if ((expr))	throw std::invalid_argument(msg)

namespace task_manager {
	StatusComponent::StatusComponent(bool status)
		: m_Status(status)
	{
	}

	StatusComponent::StatusComponent(const std::string& status)
	{
		if (status == "on") {
			m_Status = false;
		}
		else if (status == "finished") {
			m_Status = true;
		}
		else {
			THROW_INVALID_ARG_EXCEPTION_IF_TRUE(true, "[INVALID ARGUMENT]: valid values for status are \"on\" or \"finished\".");
		}

	}

	StatusComponent::StatusComponent(const char* status)
		: StatusComponent(std::string(status))
	{
	}

	void StatusComponent::SetStatus(bool status) noexcept
	{
		m_Status = status;
	}

	bool StatusComponent::GetStatus() const noexcept
	{
		return m_Status;
	}

	std::string StatusComponent::GetString() const noexcept
	{
		return m_Status ? "finished" : "on";
	}

	StatusComponent::operator bool() const noexcept
	{
		return m_Status;
	}

	bool StatusComponent::operator==(const Component& component) const noexcept
	{
		if (const auto status = dynamic_cast<const StatusComponent*>(&component)) {
			return m_Status == status->m_Status;
		}
		return false;
	}

	bool StatusComponent::operator!=(const Component& component) const noexcept
	{
		return !(*this == component);
	}

	bool StatusComponent::operator<(const Component& component) const noexcept
	{
		return false;
	}

	bool StatusComponent::operator>(const Component& component) const noexcept
	{
		return false;
	}

	bool StatusComponent::operator<=(const Component& component) const noexcept
	{
		return false;
	}

	bool StatusComponent::operator>=(const Component& component) const noexcept
	{
		return false;
	}
}