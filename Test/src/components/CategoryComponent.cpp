#include "CategoryComponent.h"

namespace task_manager {
	CategoryComponent::CategoryComponent(const char* category)
		: m_Category(category)
	{
	}

	CategoryComponent::CategoryComponent(const std::string& category)
		: m_Category(category)
	{
	}

	void CategoryComponent::SetCategory(const std::string& category) noexcept
	{
		m_Category = category;
	}

	std::string CategoryComponent::GetCategory() const noexcept
	{
		return m_Category;
	}

	std::string CategoryComponent::GetString() const noexcept
	{
		return this->GetCategory();
	}


	bool CategoryComponent::operator==(const Component& component) const noexcept
	{
		if (const auto category = dynamic_cast<const CategoryComponent*>(&component)) {
			return m_Category == category->m_Category;
		}
		return false;
	}

	bool CategoryComponent::operator!=(const Component& component) const noexcept
	{
		return !(*this == component);
	}

	bool CategoryComponent::operator<(const Component& component) const noexcept
	{
		if (const auto category = dynamic_cast<const CategoryComponent*>(&component)) {
			return m_Category < category->m_Category;
		}
		return false;
	}

	bool CategoryComponent::operator>(const Component& component) const noexcept
	{
		return !(*this < component || *this == component);
	}

	bool CategoryComponent::operator<=(const Component& component) const noexcept
	{
		return (*this < component || *this == component);
	}

	bool CategoryComponent::operator>=(const Component& component) const noexcept
	{
		return !(*this < component);
	}
}