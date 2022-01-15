#include "split-join.hpp"

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

		result.push_back(str.substr(start));

		return result;
	}

	std::vector<std::string> split(const std::string& str, const std::regex& sep)
	{
		return { std::sregex_token_iterator(str.begin(), str.end(), sep, -1), std::sregex_token_iterator() };
	}

	std::string join(const std::vector<std::string>& components, const std::string& join)
	{
		std::string result;
		for (size_t i = 0; i < components.size(); ++i)
		{
			if (i != 0)
				result += join;
			result += components[i];
		}
		return result;
	}
}
