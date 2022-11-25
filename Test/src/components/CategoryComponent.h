#pragma once
#include "Component.h"

namespace task_manager {
	class CategoryComponent final : public Component
	{
	public:
		CategoryComponent(const char* category = "");
		CategoryComponent(const std::string& category = "");

		void SetCategory(const std::string& category) noexcept;
		std::string GetCategory() const noexcept;

		std::string GetString() const noexcept override;

		bool operator==(const Component& component) const noexcept override;
		bool operator!=(const Component& component) const noexcept override;
		bool operator<(const Component& component) const noexcept override;
		bool operator>(const Component& component) const noexcept override;
		bool operator<=(const Component& component) const noexcept override;
		bool operator>=(const Component& component) const noexcept override;

	private:
		std::string m_Category;
	};
}