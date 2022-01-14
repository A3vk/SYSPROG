#include "split-joint.hpp"

namespace sp {
	std::vector<std::string> split(const std::string& str, const std::string& sep)
	{
		size_t start = 0;
		size_t end = str.find(sep);
		std::vector<std::string> result;

		while (end != std::string::npos)
		{
			result.push_back(str.substr(start, end - start));
			start = end + sep.length();
			end = str.find(sep, start);
		}

		return result;
	}

	std::vector<std::string> split(const std::string& str, const std::regex& sep)
	{
		std::vector<std::string> result;
	}

	std::string join(const std::vector<std::string>& components, const std::string& join)
	{
	}
}
