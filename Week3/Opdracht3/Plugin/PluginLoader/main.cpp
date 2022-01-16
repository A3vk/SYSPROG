#include <iostream>

#include "IPlugin.hpp"
#include "PluginWrapper.hpp"

int main(int argc, char* argv[])
{
    try {
	    using factory = sp::IPlugin* (*)();

		// Load plugin
		std::cout << argv[1] << std::endl;
		sp::PluginWrapper wrapper{ argv[1] };
	    const auto create = reinterpret_cast<factory>(wrapper.Lookup("create_instance"));
	    auto object = std::unique_ptr<sp::IPlugin>(create());
	    std::cout << "Plugin ingeladen:  " << object->Name() << " - " << object->Description() << std::endl;

		// Execute plugin
		const std::string input = "Dit is een test input string om te testen of dat deze plugin goed werkt!";
        const std::string output = object->Execute(input);
        std::cout << "Plugin uitgevoerd resultaat: " << input << " -> " << output << std::endl;
	}
	catch (const std::exception& ex) {
	    std::cerr << ex.what() << std::endl;
	    return 1;
	}
}
