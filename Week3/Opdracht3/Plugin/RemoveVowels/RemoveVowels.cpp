#include "RemoveVowels.hpp"

#include <algorithm>

namespace sp
{
	std::string RemoveVowels::Name() const
	{
		return "RemoveVowels";
	}

	std::string RemoveVowels::Description() const
	{
		return "Remove all vowels from the given text";
	}

	std::string RemoveVowels::Execute(const std::string& value) const
	{
		std::string result;
		constexpr char vowels[] = { 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };
		for (const char& letter : value)
		{
			if (!std::ranges::any_of(vowels, [&](const auto c) { return letter == c; }))
			{
				result += letter;
			}
		}
		return result;
	}
}

sp::IPlugin* create_instance()
{
	return new sp::RemoveVowels;
}
