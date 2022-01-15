#pragma once

#include "IPlugin.hpp"

namespace sp
{
	class RemoveVowels : public IPlugin
	{
	public:
		std::string Name() const override;
		std::string Description() const override;
		std::string Execute(const std::string& value) const override;
	};
}

extern "C" {
	__declspec(dllexport) sp::IPlugin* create_instance();
}