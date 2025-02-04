#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "socket.h"

#pragma comment (lib, "ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "1337"

recv_handler recvHandler;

int socketSend(SOCKET s, char * sendbuf, int len) {
  int iResult = send(s, sendbuf, len, 0);
  if (iResult == SOCKET_ERROR) {
    closesocket(s);
    WSACleanup();
    return 1;
  }
  return 2;
}

void socketSession(void * pData) {
  SOCKET ClientSocket = (SOCKET)pData;

  char recvbuf[DEFAULT_BUFLEN];
  int recvbuflen = DEFAULT_BUFLEN;

  int iResult;
  while((iResult = recv(ClientSocket, recvbuf, recvbuflen, 0)) > 0) {
    recvHandler(ClientSocket, recvbuf, iResult);
  }

  shutdown(ClientSocket, SD_SEND);
  closesocket(ClientSocket);
  WSACleanup();
}

int socketListen(recv_handler onRecv) {
  WSADATA wsaData;
  int iResult;

  recvHandler = onRecv;

  SOCKET ListenSocket = INVALID_SOCKET;
  SOCKET ClientSocket = INVALID_SOCKET;

  struct addrinfo *result = NULL;
  struct addrinfo hints;

  iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != 0) return 1;

  ZeroMemory(&hints, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;

  iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
  if ( iResult != 0 ) {
      WSACleanup();
      return 2;
  }

  ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
  if (ListenSocket == INVALID_SOCKET) {
      freeaddrinfo(result);
      WSACleanup();
      return 3;
  }

  iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
  if (iResult == SOCKET_ERROR) {
      freeaddrinfo(result);
      closesocket(ListenSocket);
      WSACleanup();
      return 4;
  }

  freeaddrinfo(result);

  iResult = listen(ListenSocket, SOMAXCONN);
  if (iResult == SOCKET_ERROR) {
      closesocket(ListenSocket);
      WSACleanup();
      return 5;
  }

  while(ClientSocket = accept(ListenSocket, NULL, NULL)) {
    if (ClientSocket == INVALID_SOCKET) continue;

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)socketSession, (void *)ClientSocket, NULL, NULL);

  }

  closesocket(ListenSocket);
  return 6;
}
