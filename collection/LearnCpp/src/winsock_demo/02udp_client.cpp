#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

namespace udp_client {

class UdpClient {
public:
  bool InitWinsock() {
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
      std::cout << "Failed to link winsock.dll!" << std::endl;
      return false;
    }

    return true;
  }

  void ReleaseWinsock() {
    WSACleanup();
  }

  void set_port(u_short port) {
    port_ = port;
  }

  void set_ip(const std::string& ip) {
    ip_ = ip;
  }

  bool Start() {
    SOCKET client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (client_socket == SOCKET_ERROR) {
      std::cout << "Failed to create socket!" << std::endl;
      return false;
    }

    sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(sockaddr_in));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port_);
    client_addr.sin_addr.S_un.S_addr = inet_addr(ip_.c_str());

    const char* kGreeting = "Hello I'm client!";
    int ret = sendto(client_socket, kGreeting, strlen(kGreeting), 0, (sockaddr*)&client_addr, sizeof(sockaddr));
    if (ret == 0) {
      std::cout << "Failed to send!" << std::endl;
      return false;
    }

    const int kBufSize = 1048;
    char buf[kBufSize] = {};

    sockaddr_in server_addr = { 0 };
    int server_addr_len = sizeof(sockaddr_in);

    ret = recvfrom(client_socket, buf, kBufSize, 0, (sockaddr*)&server_addr, &server_addr_len);
    std::cout << "Receive msg: " << buf << ". IP: " << inet_ntoa(server_addr.sin_addr)
      << " Port: " << ntohs(server_addr.sin_port) << std::endl;

    closesocket(client_socket);
    return true;
  }

private:
  u_short port_;
  std::string ip_;
};

}  // udp_client

#define PORT 6000
#define IP "127.0.0.1"

int main() {
  using namespace udp_client;
  UdpClient client;
  if (!client.InitWinsock()) {
    return 1;
  }

  client.set_port(PORT);
  client.set_ip(IP);

  client.Start();

  client.ReleaseWinsock();

  return 0;
}
