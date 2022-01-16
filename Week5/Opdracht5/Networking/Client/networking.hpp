#pragma once

#include <WS2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class WSA
{
    WSADATA data;
    static WSA instance;
public:
    WSA();
    ~WSA();
};