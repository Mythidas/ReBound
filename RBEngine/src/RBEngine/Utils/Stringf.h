#pragma once

#include <vector>
#include <string>

namespace RB
{
	class Stringf
	{
	public:
		static std::vector<std::string> Split(const std::string& source, const char delim);
		static std::vector<std::string> EachLine(const std::string& source);
	};
}