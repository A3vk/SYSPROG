#include "PluginWrapper.hpp"

#include <stdexcept>
#include <sstream>
#include <Windows.h>

namespace sp
{
	PluginWrapper::PluginWrapper(const std::string& path)
	{
		_plugin = LoadLibraryA(path.c_str());
		if (!_plugin)
		{
			std::ostringstream oss;
			oss << "plugin could not be found, err " << GetLastError();
			throw std::runtime_error(oss.str());
		}
	}

	PluginWrapper::~PluginWrapper()
	{
		Cleanup();
	}

	PluginWrapper::PluginWrapper(PluginWrapper&& other)
	{
		Move(std::move(other));
	}

	PluginWrapper& PluginWrapper::operator=(PluginWrapper&& other)
	{
		if (&other != this)
		{
			Cleanup();
			Move(std::move(other));
		}
		return *this;
	}

	void* PluginWrapper::Lookup(const std::string& symbol) const
	{
		void* result = GetProcAddress(reinterpret_cast<HMODULE>(_plugin), symbol.c_str());
		if(!result)
		{
			std::ostringstream oss;
			oss << "symbol " << symbol << " could not be found, err " << GetLastError();
			throw std::runtime_error(oss.str());
		}
		return result;
	}

	void PluginWrapper::Cleanup()
	{
		if (_plugin)
		{
			FreeLibrary(reinterpret_cast<HMODULE>(_plugin));
		}
	}

	void PluginWrapper::Move(PluginWrapper&& other)
	{
		_plugin = other._plugin;
		other._plugin = nullptr;
	}
}
