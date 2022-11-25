#pragma once
#include <vector>
#include <string>

namespace string_utility {
	class StringParser
	{
	public:
		static std::vector<std::string> Split(const std::string& str);
		static std::vector<std::wstring> Split(const std::wstring& wstr);
		static std::vector<std::string> Split(const std::string& str, unsigned char separator);
		static std::vector<std::wstring> Split(const std::wstring& str, wchar_t separator);

		static std::string ToLowerCase(const std::string& str) noexcept;
		static std::string ToUpperCase(const std::string& str) noexcept;

		static std::wstring ToLowerCase(const std::wstring& str) noexcept;
		static std::wstring ToUpperCase(const std::wstring& str) noexcept;
	};
}