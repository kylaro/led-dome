
#include "ADDRESS_CONFIG.h"
#include "udpsend_windows.h"
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>


using namespace std;

#pragma comment(lib, "Ws2_32.lib")


int udpSend_windows(char* pkt) {
    static int init = 0;
    static SOCKET s;
    static struct sockaddr_in clientService;


    if (init == 0) {
        //https://docs.microsoft.com/en-us/windows/win32/winsock/initializing-winsock
        WSADATA wsaData;

        int iResult;

        // Initialize Winsock
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            printf("WSAStartup failed: %d\n", iResult);
            return 1;
        }

        s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        clientService.sin_family = AF_INET;
        clientService.sin_addr.s_addr = inet_addr(HOSTNAME_WIN);
        clientService.sin_port = htons(PORT_WIN);

        if (connect(s, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
            //std::cout << "oh no it didn't work" << std::endl;
        }

        init = 1;
    }

    if (send(s, pkt, PACKET_LENGTH_WIN, 0) == SOCKET_ERROR) {
        init = 0;
        std::cout << ".";
    }

    return 0;

}