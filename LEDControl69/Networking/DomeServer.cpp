#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#include "DomeServer.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

namespace server {

    posepack_t* pose3D;

    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char* recvbuf;
    int recvbuflen;
    int connected = 0;

    int initialize() {
        // Initialize Winsock
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            printf("WSAStartup failed with error: %d\n", iResult);
            return 0;
        }

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        // Resolve the server address and port
        iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

        if (iResult != 0) {
            printf("getaddrinfo failed with error: %d\n", iResult);
            WSACleanup();
            return 0;
        }
        return 1;
    }

    int getClient() {
        // Create a SOCKET for connecting to server
        ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (ListenSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
            //while (1) {}
           // return 1;
            return 0;

        }

        // Setup the TCP listening socket
        iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            printf("bind failed with error: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            closesocket(ListenSocket);
            WSACleanup();
            //while (1) {}
            //return 1;
            return 0;
        }

        freeaddrinfo(result);

        iResult = listen(ListenSocket, SOMAXCONN);
        if (iResult == SOCKET_ERROR) {
            printf("listen failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 0;
        }
        printf("Waiting for client...");
        // Accept a client socket
        ClientSocket = accept(ListenSocket, NULL, NULL);

        if (ClientSocket == INVALID_SOCKET) {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
           
            return 0;
        }
        // No longer need server socket
        closesocket(ListenSocket);
        return 1;
    }

    void printPosePack(posepack_t* pose3D) {

        printf("left hand:\tx%.2f\ty%.2f\tz%.2f\tperc:%.2f\n", pose3D->left_hand.x, pose3D->left_hand.y, pose3D->left_hand.z, pose3D->left_hand.percussion);
        printf("right hand:\tx%.2f\ty%.2f\tz%.2f\tperc:%.2f\n", pose3D->right_hand.x, pose3D->right_hand.y, pose3D->right_hand.z, pose3D->right_hand.percussion);
        printf("left foot:\tx%.2f\ty%.2f\tz%.2f\tperc:%.2f\n", pose3D->left_foot.x, pose3D->left_foot.y, pose3D->left_foot.z, pose3D->left_foot.percussion);
        printf("right foot:\tx%.2f\ty%.2f\tz%.2f\tperc:%.2f\n", pose3D->right_foot.x, pose3D->right_foot.y, pose3D->right_foot.z, pose3D->right_foot.percussion);
    }

    int receiveAndSend() {
        // Receive until the peer shuts down the connection

        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult == 9) {
            printf("Established Connection\n");
            connected = 1;
        }
        else if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

            pose3D = (posepack_t*)recvbuf;
            printPosePack(pose3D);

            // Echo the buffer back to the sender
            /*
            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                //while (1) {}
                //return 1;
                return 0;
            }
            printf("Bytes sent: %d\n", iSendResult);
            */
        }
        else if (iResult == 0) {
            printf("Connection closing...\n");
            return 0;
        } else {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 0;
            //
            //while (1) {}
            //return 1;
        }
        
        return 1;
    }

    int mainloop() {
        //State machine kinda:
        /*                              client connect      client disconnect
        1. initialize server                x                   x
        2. wait for client                  3                   x
        3. receive and send loop            x                   2
        
        */
        
        while (1) {
            while (initialize() != 1) {};
            while (getClient() != 1) { while (initialize() != 1) {}; };
            while (receiveAndSend() == 1) { connected = 1; };
            connected = 0;
        }
        

    }
    int start()
    {
        recvbuf = (char*)calloc(1, sizeof(posepack_t));
        recvbuflen = sizeof(posepack_t);
        pose3D = (posepack_t*)calloc(1, sizeof(posepack_t));
        mainloop();
        //mainloop is while 1, so we won't make it here.


        // shutdown the connection since we're done
        iResult = shutdown(ClientSocket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            printf("shutdown failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            while (1) {}
            return 1;
        }

        // cleanup
        closesocket(ClientSocket);
        WSACleanup();
        while (1) {}
        return 0;
    }
}
