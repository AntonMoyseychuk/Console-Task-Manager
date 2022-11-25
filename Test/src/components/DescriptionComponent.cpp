#include "DescriptionComponent.h"

namespace task_manager {
	DescriptionComponent::DescriptionComponent(const char* description)
		: m_Description(description)
	{
	}

	DescriptionComponent::DescriptionComponent(const std::string& description)
		: m_Description(description)
	{
	}

	void DescriptionComponent::SetDescription(const std::string& description) noexcept
	{
		m_Description = description;
	}

	std::string DescriptionComponent::GetDescription() const noexcept
	{
		return m_Description;
	}

	std::string DescriptionComponent::GetString() const noexcept
	{
		return this->GetDescription();
	}
	bool DescriptionComponent::operator==(const Component& component) const noexcept
	{
		if (const auto desc = dynamic_cast<const DescriptionComponent*>(&component)) {
			return m_Description == desc->m_Description;
		}
		return false;
	}
	bool DescriptionComponent::operator!=(const Component& component) const noexcept
	{
		return !(*this == component);
	}
	bool DescriptionComponent::operator<(const Component& component) const noexcept
	{
		if (const auto desc = dynamic_cast<const DescriptionComponent*>(&component)) {
			return m_Description < desc->m_Description;
		}
		return false;
	}
	bool DescriptionComponent::operator>(const Component& component) const noexcept
	{
		return !(*this < component || *this == component);
	}
	bool DescriptionComponent::operator<=(const Component& component) const noexcept
	{
		return (*this < component || *this == component);
	}
	bool DescriptionComponent::operator>=(const Component& component) const noexcept
	{
		return !(*this < component);
	}
}