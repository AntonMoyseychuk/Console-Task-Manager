#pragma once
#include "Component.h"

namespace task_manager {
	class NameComponent final : public Component
	{
	public:
		NameComponent(const char* name = "");
		NameComponent(const std::string& name = "");

		void SetName(const std::string& name) noexcept;
		std::string GetName() const noexcept;

		std::string GetString() const noexcept override;

		bool operator==(const Component& component) const noexcept override;
		bool operator!=(const Component& component) const noexcept override;
		bool operator< (const Component& component) const noexcept override;
		bool operator> (const Component& component) const noexcept override;
		bool operator<=(const Component& component) const noexcept override;
		bool operator>=(const Component& component) const noexcept override;

	private:
		std::string m_Name;
	};
}
