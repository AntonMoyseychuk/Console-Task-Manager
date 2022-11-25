#include "NameComponent.h"

namespace task_manager {
	NameComponent::NameComponent(const char* name)
		: m_Name(name)
	{
	}

	NameComponent::NameComponent(const std::string& name)
		: m_Name(name)
	{
	}

	void NameComponent::SetName(const std::string& name) noexcept
	{
		m_Name = name;
	}

	std::string NameComponent::GetName() const noexcept
	{
		return m_Name;
	}

	std::string NameComponent::GetString() const noexcept
	{
		return this->GetName();
	}

	bool NameComponent::operator==(const Component& component) const noexcept
	{
		if (const auto name = dynamic_cast<const NameComponent*>(&component)) {
			return m_Name == name->m_Name;
		}
		return false;
	}

	bool NameComponent::operator!=(const Component& component) const noexcept
	{
		return !(*this == component);
	}

	bool NameComponent::operator<(const Component& component) const noexcept
	{
		if (const auto name = dynamic_cast<const NameComponent*>(&component)) {
			return m_Name < name->m_Name;
		}
		return false;
	}

	bool NameComponent::operator>(const Component& component) const noexcept
	{
		return !(*this < component || *this == component);
	}

	bool NameComponent::operator<=(const Component& component) const noexcept
	{
		return (*this < component || *this == component);
	}

	bool NameComponent::operator>=(const Component& component) const noexcept
	{
		return !(*this < component);
	}
}
