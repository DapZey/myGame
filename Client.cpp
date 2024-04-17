//
// Created by benra on 3/11/2024.
//

#include "Client.h"
#include <ws2tcpip.h>

int Client::run() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    // Create a socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "socket failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Test Winsock functionality (e.g., connect to a server)

    // Clean up Winsock
    closesocket(sock);
    WSACleanup();
    return 0;
}
