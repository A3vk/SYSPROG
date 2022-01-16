#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <Windows.h>

std::vector<std::string> scan_dir(const std::string& path, const std::string& ext)
{
	std::vector<std::string> plugins;
	for (const auto& entry : std::filesystem::directory_iterator { path })
	{
		std::string filename{ entry.path().string() };
		if (filename.substr(filename.size() - ext.size(), ext.size()) == ext)
		{
			plugins.push_back(filename);
		}
	}
	return plugins;
}

void TestPlugin2(const std::string& plugin)
{
	// pid_t pid = fork();

}

void TestPlugin(const std::string& plugin)
{
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInfo;

	ZeroMemory(&startupInfo, sizeof startupInfo);
	startupInfo.cb = sizeof startupInfo;
	ZeroMemory(&processInfo, sizeof processInfo);

	std::string program = "PluginLoader.exe " + plugin;
	if (!CreateProcess(nullptr, std::wstring(program.begin(), program.end()).data(), nullptr, nullptr, false, 0, nullptr, nullptr, &startupInfo, &processInfo))
	{
		std::cerr << "CreateProcess failed (" << GetLastError() << ")" << std::endl;
		return;
	}

	WaitForSingleObject(processInfo.hProcess, INFINITE);
	DWORD status;
	GetExitCodeProcess(processInfo.hProcess, &status);
	if (!status)
	{
		std::cout << "Plugin `" << plugin << "`: SUCCEEDED!" << std::endl;
	}
	else
	{
		std::cerr << "Plugin `" << plugin << "`: FAILED! Error: " << GetLastError() << std::endl;
	}

	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
}

int main()
{
	// Find plugins
	std::vector<std::string> files{ scan_dir("Plugins", "plug") };

	for (const auto& file : files)
	{
		TestPlugin(file);
	}

	system("pause");
}

// int main()
// {
// 	try {
// 		std::vector<std::string> files{ scan_dir("Plugins", "plug") };
//
// 		std::vector<sp::PluginWrapper> plugins;
// 		for (const std::string& file : files)
// 		{
// 			plugins.emplace_back(file);
// 		}
//
// 		using factory = sp::IPlugin* (*)();
// 		std::vector<std::unique_ptr<sp::IPlugin>> objects;
// 		for (const sp::PluginWrapper& wrapper : plugins)
// 		{
// 			factory func = reinterpret_cast<factory>(wrapper.Lookup("create_instance"));
// 			objects.emplace_back(func());
// 		}
//
// 		std::cout << "Wat is het path naar de input file: ";
// 		std::string fileName;
// 		std::cin >> fileName;
// 		std::ifstream inputFile(fileName);
// 		if (!inputFile.is_open())
// 		{
// 			std::cout << "File does not exist!" << std::endl;
// 			std::system("pause");
// 			exit(EXIT_FAILURE);
// 		}
// 		std::string inputString((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
//
// 		std::cout << "Type een van de volgende cijfers om een plugin uit te voeren of q om te stoppen:" << std::endl;
// 		for (int i = 0; i < objects.size(); ++i) {
// 			std::cout << "[" << i << "] " << objects[i]->Name() << ": " << objects[i]->Description() << std::endl;
// 		}
//
// 		while (true)
// 		{
// 			char input = getchar();
// 			if (input == '\n') continue;
// 			if (input == 'q')
// 			{
// 				break;
// 			}
//
// 			int index = (int)input - 48;
// 			if (index >= 0 && index < objects.size())
// 			{
// 				inputString = objects[index]->Execute(inputString);
// 				std::cout << "Plugin uitgevoerd resultaat: " << inputString << "\nType nog een cijfer om nog een plugin uit te voeren of type q om te stoppen:" << std::endl;
// 			} else
// 			{
// 				std::cout << "Geen geldige input gegeven probeer nogmaals" << std::endl;
// 			}
// 		}
// 		std::cout << "Resultaat: " << inputString << std::endl;
// 	}
// 	catch (const std::exception& ex) {
// 		std::cerr << ex.what() << std::endl;
// 		return 1;
// 	}
//
// 	std::system("pause");
// }
