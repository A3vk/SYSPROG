#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <sstream>
#include <fstream>
#include <thread>

#include "networking.hpp"

std::vector<std::string> wordList;

void throw_if_min1(int x)
{
	if (x == -1) {
		WCHAR buf;
		int iResult = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, WSAGetLastError(), 0, &buf, 0, nullptr);
		std::ostringstream msg;
		msg << buf;
		LocalFree((HLOCAL)buf);
		throw std::runtime_error{ msg.str() };
	}
}

void work(int client, struct sockaddr* clientEndpoint)
{
	const struct sockaddr_in* addr = reinterpret_cast<const struct sockaddr_in*>(clientEndpoint);
	std::vector<char> cbuf(INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &addr->sin_addr, cbuf.data(), cbuf.size());

	std::cout << "server: got connection from " << cbuf.data() << ":" << ntohs(addr->sin_port) << std::endl;

	std::vector<char> buf(1024);
	int n = 0;
	throw_if_min1(n = recv(client, buf.data(), buf.size(), 0));
	std::cout << "server: read " << n << " bytes from client" << std::endl;
	int random_number = std::rand() % wordList.size();
	throw_if_min1(send(client, wordList[random_number].data(), n, 0));
	std::cout << "server: connection closed by client" << std::endl;
	throw_if_min1(closesocket(client));
}

int main()
{
	std::ifstream file("nl.words.txt");
	std::string word;
	while (std::getline(file, word))
	{
		wordList.push_back(word);
	}

	try
	{
		int server{ 0 };
		throw_if_min1(server = socket(AF_INET, SOCK_STREAM, 0));
	
		struct sockaddr_in sa;
		std::memset(&sa, 0, sizeof(struct sockaddr_in));
		sa.sin_family = AF_INET;
		sa.sin_port = htons(4242);
		throw_if_min1(inet_pton(AF_INET, "localhost", &sa.sin_addr.s_addr));
	
		throw_if_min1(bind(server, reinterpret_cast<struct sockaddr*>(&sa), sizeof sa));
		throw_if_min1(listen(server, SOMAXCONN));
	
		while (true)
		{
			int client = 0;
			struct sockaddr_storage clientStorage;
			socklen_t len{ sizeof(struct sockaddr_storage) };
			struct sockaddr* clientEndpoint = reinterpret_cast<struct sockaddr*>(&clientStorage);
	
			std::cout << "server: waiting for client\n";
			throw_if_min1(client = accept(server, clientEndpoint, &len));
	
			std::thread clientThread{ work, client, clientEndpoint };
		}
		throw_if_min1(closesocket(server));
	}
	catch (const std::exception& ex)
	{
		std::cerr << "server: " << ex.what() << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}
	system("pause");
	return EXIT_SUCCESS;
}
