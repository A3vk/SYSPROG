#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

#include "networking.hpp"

void throw_if_min1(int x)
{
    if (x == -1) {
        WCHAR buf;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, WSAGetLastError(), 0, &buf, 0, nullptr);
        std::ostringstream msg;
        msg << buf;
        LocalFree((HLOCAL)buf);
        throw std::runtime_error{ msg.str() };
    }
}

std::string read_line(int sock) {
    std::string result;
    char c{};
    int n;
    while ((n = recv(sock, &c, 1, 0)) != 0 && c != '\n') {
        throw_if_min1(n);
        result += c;
    }
    return result;
}

int main()
{
    try {
        int server = 0;
        throw_if_min1(server = socket(AF_INET, SOCK_STREAM, 0));
        
        struct sockaddr_in sa = {};
        sa.sin_family = AF_INET;
        sa.sin_port = htons(4242);
        throw_if_min1(inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr.s_addr));
        
        throw_if_min1(connect(server, reinterpret_cast<sockaddr*>(&sa), sizeof(sa)));

        const std::string request = "Requesting word";
        throw_if_min1(send(server, request.c_str(), request.size(), 0));

        const std::string resp{ read_line(server) };
        std::cout << "client: server gave the following word: " << resp << std::endl;
        
        throw_if_min1(closesocket(server));
    }
    catch (const std::exception& ex) {
        std::cerr << "client: " << ex.what() << '\n';
        system("pause");
        return EXIT_FAILURE;
    }
    system("pause");
    return EXIT_SUCCESS;
}
