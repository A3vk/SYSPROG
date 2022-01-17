#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <sstream>
#include <fstream>
#include <random>
#include <thread>

#include "networking.hpp"

std::vector<std::string> wordList;
std::random_device random_device;
std::mt19937 engine;
std::uniform_int_distribution<int> distribution;

void throw_if_min1(int x, const char* message = nullptr)
{
	if (x == -1) {
		WCHAR buf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, WSAGetLastError(), 0, &buf, 0, nullptr);
		std::ostringstream msg;
		msg << buf;
		if (message) {
			msg << ", " << message;
		}
		LocalFree((HLOCAL)buf);
		throw std::runtime_error{ msg.str() };
	}
}

void work(int client)
{
    std::vector<char> buf(1024);
    int n = n = recv(client, buf.data(), buf.size(), 0);
    throw_if_min1(n);
    std::cout << "server: read " << n << " bytes from client\n";

	const std::string word = wordList[distribution(engine)];
	std::cout << "server: chosen the word `" << word << "` to send to the client" << std::endl;
	throw_if_min1(send(client, word.data(), word.size(), 0), "Could not send data");

	throw_if_min1(closesocket(client), "Could not close client socket");
}

int main() {
    // Initialize the word list
    std::ifstream file("nl.words.txt");
    std::string word;
    while (std::getline(file, word))
    {
        wordList.push_back(word);
    }

    // Initialize random engine
    engine = std::mt19937(random_device());
    distribution = std::uniform_int_distribution<int>(0, wordList.size() - 1);

    try {
        int server;
        throw_if_min1(server = socket(AF_INET, SOCK_STREAM, 0));
        
        sockaddr_in sa = {};
        sa.sin_family = AF_INET;
        sa.sin_port = htons(4242);
        throw_if_min1(inet_pton(AF_INET, "localhost", &sa.sin_addr.s_addr));
        
        throw_if_min1(bind(server, reinterpret_cast<sockaddr*>(&sa), sizeof(sa)));
        throw_if_min1(listen(server, SOMAXCONN));

        while (true) {
            int client{ 0 };
            sockaddr_storage clientStorage;
            socklen_t length{ sizeof(struct sockaddr_storage) };
            const auto clientEndpoint = reinterpret_cast<struct sockaddr*>(&clientStorage);

            throw_if_min1(client = accept(server, clientEndpoint, &length));
            
            const auto* address = reinterpret_cast<const struct sockaddr_in*>(clientEndpoint);
            std::vector<char> charBuffer(INET_ADDRSTRLEN);
            inet_ntop(AF_INET, &address->sin_addr, charBuffer.data(), charBuffer.size());
            
            std::cout << "server: got connection from " << charBuffer.data() << ":" << ntohs(address->sin_port) << std::endl;
            
            std::thread clientThread{ work, client };
            clientThread.join();
        }
        throw_if_min1(closesocket(server));
    }
    catch (const std::exception& ex) {
        std::cerr << "server: " << ex.what() << '\n';
        system("pause");
        return EXIT_FAILURE;
    }
    system("pause");
    return EXIT_SUCCESS;
}