#pragma once

#include <string>

namespace sp
{
	class IPlugin
	{
	public:
		virtual ~IPlugin() = default;
		virtual std::string Name() const = 0;
		virtual std::string Description() const = 0;
		virtual std::string Execute(const std::string& value) const = 0;
	};
}