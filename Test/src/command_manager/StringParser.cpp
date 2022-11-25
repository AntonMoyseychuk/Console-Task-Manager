#include <algorithm>
#include <stdexcept>
#include <cwctype>
#include "StringParser.h"


namespace string_utility {
	std::vector<std::string> StringParser::Split(const std::string& str)
	{
		std::vector<std::string> result;
		if (str.empty()) {
			return result;
		}
		// 0         1         2         3
		// 01234567890123456789012345678901
		//"  AAAA    "dsad adasda"  "sdfsd""
		for (auto start = str.find_first_not_of(" "), end = start; str.begin() + start != str.end(); ) {
			if (str.find_first_of('\"', start) == start) {
				end = str.find_first_of('\"', ++start);
				if (end > str.size()) {
					throw std::invalid_argument("[PARSER ERROR]: missing closing tabs.");
				}
				result.push_back(str.substr(start, end - start));
			}
			else {
				end = std::clamp(str.find_first_of(" ", start), size_t(0), str.size());
				result.push_back(str.substr(start, end - start));
			}

			start = std::clamp(str.find_first_not_of(' ', end + 1), size_t(0), str.size());
		}

		return result;
	}

	std::vector<std::wstring> StringParser::Split(const std::wstring& wstr)
	{
		std::vector<std::wstring> result;

		for (auto start = wstr.find_first_not_of(L" "), end = start; wstr.begin() + start != wstr.end(); ) {
			if (wstr.find_first_of(L"\"", start) == start) {
				end = wstr.find_first_of(L"\"", ++start);
				if (end > wstr.size()) {
					throw std::invalid_argument("[PARSER ERROR]: missing closing tabs.");
				}
				result.push_back(wstr.substr(start, end - start));
			}
			else {
				end = std::clamp(wstr.find_first_of(L" ", start), size_t(0), wstr.size());
				result.push_back(wstr.substr(start, end - start));
			}

			start = std::clamp(wstr.find_first_not_of(L" ", end + 1), size_t(0), wstr.size());
		}

		return result;
	}

	std::vector<std::string> StringParser::Split(const std::string& str, unsigned char separator)
	{
		std::vector<std::string> result;

		for (auto start = str.find_first_not_of(separator), end = start; str.begin() + start != str.end(); ) {
			end = std::clamp(str.find_first_of(separator, start), size_t(0), str.size());
			result.push_back(str.substr(start, end - start));

			start = std::clamp(str.find_first_not_of(separator, end + 1), size_t(0), str.size());
		}

		return result;
	}

	std::vector<std::wstring> StringParser::Split(const std::wstring& str, wchar_t separator)
	{
		std::vector<std::wstring> result;

		for (auto start = str.find_first_not_of(separator), end = start; str.begin() + start != str.end(); ) {
			end = std::clamp(str.find_first_of(separator, start), size_t(0), str.size());
			result.push_back(str.substr(start, end - start));

			start = std::clamp(str.find_first_not_of(separator, end + 1), size_t(0), str.size());
		}

		return result;
	}

	std::string StringParser::ToLowerCase(const std::string& str) noexcept
	{
		std::string result;
		result.resize(str.size());

		std::transform(str.begin(), str.end(), result.begin(), tolower);
		return result;
	}

	std::string StringParser::ToUpperCase(const std::string& str) noexcept
	{
		std::string result;
		result.resize(str.size());

		std::transform(str.begin(), str.end(), result.begin(), toupper);
		return result;
	}

	std::wstring StringParser::ToLowerCase(const std::wstring& str) noexcept
	{
		std::wstring result;
		result.resize(str.size());

		std::transform(str.begin(), str.end(), result.begin(), towlower);
		return result;
	}

	std::wstring StringParser::ToUpperCase(const std::wstring& str) noexcept
	{
		std::wstring result;
		result.resize(str.size());

		std::transform(str.begin(), str.end(), result.begin(), towupper);
		return result;
	}
}
