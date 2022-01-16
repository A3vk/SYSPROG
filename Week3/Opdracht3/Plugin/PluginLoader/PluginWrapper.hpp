#pragma once

#include <string>

namespace sp {
	class PluginWrapper
	{
	public:
		PluginWrapper(const std::string& path);
		~PluginWrapper();

		PluginWrapper(const PluginWrapper&) = delete;
		PluginWrapper& operator=(const PluginWrapper&) = delete;

		PluginWrapper(PluginWrapper&& other);
		PluginWrapper& operator=(PluginWrapper&& other);

		void* Plugin() const { return _plugin; }
		void* Lookup(const std::string& symbol) const;

	private:
		void* _plugin{ nullptr };

		void Cleanup();
		void Move(PluginWrapper&& other);
	};
}
