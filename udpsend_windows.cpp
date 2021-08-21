
#include "udpsend_windows.h"
#include <string>
#include <winsock2.h>
#include <iostream>


using namespace std;



int udpSend_windows( char *pkt) {
    static int init = 0;
    static SOCKET s;
    static struct sockaddr_in clientService;
    

    if (init == 0){
        s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        clientService.sin_family = AF_INET;
        clientService.sin_addr.s_addr = inet_addr( HOSTNAME_WIN);
        clientService.sin_port = htons( PORT_WIN );

        if (connect( s, (SOCKADDR*) &clientService, sizeof(clientService) ) == SOCKET_ERROR) {
            std::cout << "oh no it didn't work" << std::endl;
        }

        init = 1;
    }

    if ( send(s,pkt,PACKET_LENGTH_WIN,0) == SOCKET_ERROR){
        init = 0;
        std::cout << "socket reinit" << std::endl;
    }

    return 0;

    //const char* srcIP = "192.168.1.1";

    /*const char* destIP = HOSTNAME_WIN;
    sockaddr_in dest;
    sockaddr_in local;
    WSAData data;
    WSAStartup(MAKEWORD(2, 2), &data);

    local.sin_family = AF_INET;
    //inet_pton(AF_INET, srcIP, &local.sin_addr.s_addr);
    local.sin_port = htons(0);

    dest.sin_family = AF_INET;
    //inet_pton(AF_INET, destIP, &dest.sin_addr.s_addr);
    dest.sin_port = htons(PORT_WIN);

    SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bind(s, (sockaddr *)&local, sizeof(local));

    sendto(s, pkt, PACKET_LENGTH_WIN, 0, (sockaddr *)&dest, sizeof(dest));

    closesocket(s);
    WSACleanup();

    return 0;*/




    /*
    int BufLen = PACKET_LENGTH_WIN;
    //const char* toSend = "foobar";
    //strcpy(SendBuf, toSend);
    SOCKET SendSocket = socket(AF_INET , SOCK_STREAM , 0 );

    struct sockaddr_in ClientAddr;
    int clientAddrSize = (int)sizeof(ClientAddr);
    short port = PORT_WIN;
    const char* local_host = HOSTNAME_WIN;
    ClientAddr.sin_family = AF_INET;
    ClientAddr.sin_port = htons(port);
    ClientAddr.sin_addr.s_addr = inet_addr(local_host);
    //puts("Sending a datagram to the receiver...");

    int clientResult = sendto(SendSocket,
                              SendBuf, BufLen, 0, (SOCKADDR *) & ClientAddr, clientAddrSize);
    return clientResult;
     */
}