#pragma once
#include "Component.h"

namespace task_manager {
	class StatusComponent final : public Component
	{
	public:
		StatusComponent(bool status = false);
		explicit StatusComponent(const std::string& status = "on");
		explicit StatusComponent(const char* status = "on");

		void SetStatus(bool status) noexcept;
		bool GetStatus() const noexcept;

		std::string GetString() const noexcept override;

		operator bool() const noexcept;

		bool operator==(const Component& component) const noexcept override;
		bool operator!=(const Component& component) const noexcept override;
		bool operator< (const Component& component) const noexcept override;// plug
		bool operator> (const Component& component) const noexcept override;// plug
		bool operator<=(const Component& component) const noexcept override;// plug
		bool operator>=(const Component& component) const noexcept override;// plug

	private:
		bool m_Status;
	};
}