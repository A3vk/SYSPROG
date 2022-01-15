#include "UpperCasePlugin.hpp"

#include <algorithm> 
#include <string>  

namespace sp
{
	std::string UpperCasePlugin::Name() const
	{
		return "UpperCasePlugin";
	}

	std::string UpperCasePlugin::Description() const
	{
		return "Convert the given text to upper case";
	}

	std::string UpperCasePlugin::Execute(const std::string& value) const
	{
		std::string result = value;
		std::ranges::transform(result, result.begin(), ::toupper);
		return result;
	}
}

sp::IPlugin* create_instance()
{
	return new sp::UpperCasePlugin;
}
