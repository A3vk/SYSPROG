#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random-engine.hpp>
#include <split-join.hpp>
#include <unordered_map>

int main() {
	std::ifstream file("Alice_in_Wonderland.txt");

	if (!file.is_open())
	{
		std::cout << "Could not open file!" << std::endl;
		std::system("pause");
		exit(EXIT_FAILURE);
	}

	std::vector<std::string> lines;
	std::string line;
	while (std::getline(file, line))
	{
		lines.push_back(line);
	}

	const auto& random = RandomEngine::GetInstance();

	std::unordered_map<std::string, int> wordCount;
	std::regex pattern{ R"([^[:alpha:]]+)" };
	for (int i = 0; i < 10; i++)
	{
		for (const auto& word : sp::split(random.RandomElement(lines), pattern))
		{
			if (!word.empty()) wordCount[word]++;
		}
	}

	for (const auto& [word, count] : wordCount)
	{
		std::cout << word << ": " << std::string(count, '*') << std::endl;
	}

	std::system("pause");
}
