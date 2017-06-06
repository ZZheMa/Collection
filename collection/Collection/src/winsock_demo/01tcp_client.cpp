#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>

#include <winsock2.h>  // 包含网络通信头文件

#pragma comment(lib, "ws2_32.lib")  // 程序在链接的时候将该库链接进去。显示链接动态库。

#define PORT 8888
#define SERVER_IP "127.0.0.1"
#define  BUFFER_SIZE 256

static const std::string kExitFlag = "-1";

int main() {
  // 初始化socket dll。
  WORD winsock_version = MAKEWORD(2,2);
  WSADATA wsa_data;
  if (WSAStartup(winsock_version, &wsa_data) != 0) {
    std::cout << "Failed to init socket dll!" << std::endl;
    return 1;
  }

  SOCKET client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (client_socket == INVALID_SOCKET) {
    std::cout << "Failed to create server socket!" << std::endl;
    return 2;
  }

  // 绑定IP和端口。
  sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
  if (connect(client_socket, (LPSOCKADDR)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
    std::cout << "Failed to connect server!" << std::endl;
    return 3;
  }

  char recv_data[BUFFER_SIZE] = {};

  while (true) {
    std::string data;
    std::cout << "Input data: ";
    std::cin >> data;

    if (send(client_socket, data.c_str(), data.size(), 0) < 0) {
      std::cout << "Failed to send data!" << std::endl;
      break;
    }

    int ret = recv(client_socket, recv_data, BUFFER_SIZE, 0);
    if (ret < 0) {
      std::cout << "Failed to receive data!" << std::endl;
      break;
    }

    std::cout << "Receive data from server: " << recv_data << std::endl;

    if (data == kExitFlag) {
      std::cout << "Exit!" << std::endl;
      break;
    }
  }

  closesocket(client_socket);
  WSACleanup();

  return 0;
}