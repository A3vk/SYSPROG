#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <thread>

std::vector<std::mutex> mutexes;
std::mutex mtx;

void work(const std::string& timestamp, size_t numberOfFiles, const std::string& value)
{
	for (size_t i = 1; i <= numberOfFiles; i++) {
		std::unique_lock<std::mutex> lock{ mutexes[i - 1] };
		std::string filename = timestamp + "-" + std::to_string(i) + ".txt";
		std::ofstream file(filename, std::ios_base::app);
		file << value << std::endl;
		file.close();
	}

	for (size_t i = 1; i <= numberOfFiles; i++) {
		std::unique_lock<std::mutex> lock{ mutexes[i - 1] };
		std::string filename = timestamp + "-" + std::to_string(i) + ".txt";
		std::ifstream file(filename);
		std::cout << file.rdbuf() << std::endl;
		file.close();
	}
}

int main()
{
	// Create the files
	auto t = std::time(nullptr);
	tm timeInfo;
	localtime_s(&timeInfo, &t);
	std::ostringstream oss;
	oss << std::put_time(&timeInfo, "%Y%m%d%H%M%S");
	std::string timestamp = oss.str();

	// Create a mutex for each file
	size_t numberOfFiles = 2;
	std::vector<std::mutex> list(numberOfFiles);
	mutexes.swap(list);

	for (size_t i = 1; i <= numberOfFiles; i++) {
		std::string filename = timestamp + "-" + std::to_string(i) + ".txt";
		std::ofstream file(filename);
		file.close();
	}

	std::thread t1{ work, timestamp, 2, "Hey, Ik kom van af thread 1!" };
	std::thread t2{ work, timestamp, 2, "Hey, Ik kom van af thread 2!" };

	t1.join();
	t2.join();

	system("pause");
}
