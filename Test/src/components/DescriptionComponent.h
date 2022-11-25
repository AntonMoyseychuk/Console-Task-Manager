#pragma once
#include "Component.h"

namespace task_manager {
	class DescriptionComponent final : public Component
	{
	public:
		DescriptionComponent(const char* description = "");
		DescriptionComponent(const std::string& description = "");

		void SetDescription(const std::string& description) noexcept;
		std::string GetDescription() const noexcept;

		std::string GetString() const noexcept override;

		bool operator==(const Component& component) const noexcept override;
		bool operator!=(const Component& component) const noexcept override;
		bool operator< (const Component& component) const noexcept override;
		bool operator> (const Component& component) const noexcept override;
		bool operator<=(const Component& component) const noexcept override;
		bool operator>=(const Component& component) const noexcept override;

	private:
		std::string m_Description;
	};
}
