#include "throw.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "networking.hpp"

void __throw_if_min1(int x, const char* file, unsigned line)
{
    if (x == -1) {
        WCHAR buf;
        int iResult = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            WSAGetLastError(),
            0,
            &buf,
            0,
            nullptr);
        std::ostringstream msg;
        std::string f{ file };
        msg << buf << " (" << f.substr(f.rfind('/') + 1) << ":" << line << ")";
        LocalFree((HLOCAL)buf);
        throw std::runtime_error{ msg.str() };
    }
}
