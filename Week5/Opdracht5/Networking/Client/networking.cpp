#include "networking.hpp"

#include <iostream>

WSA WSA::instance;

WSA::WSA() {
    int iResult = WSAStartup(MAKEWORD(2, 2), &data);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed with error: " << iResult << '\n';
    }
}

WSA::~WSA() {
    WSACleanup();
}