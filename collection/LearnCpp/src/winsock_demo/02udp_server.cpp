#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

// 1.TCP是面向连接的，它在通信之前需要进行三次握手来确定双方是否已经准备好了。
// 因此，双方很清楚数据是从哪里来的。
// 而UDP是面向数据包的，因此就好像寄快递一样，你必须在快递上写一张纸条，上面填好姓名，
// 地址等信息，填好之后，接收者才知道该东西是由谁寄过来的。
// 而UDP的收发函数recvform和sendto了sockaddr结构的地址，用于保存从哪里发来的和发送到哪里的地址信息。

// 2.UDP套接口是无连接的、不可靠的数据报协议；既然他不可靠为什么还要用呢？
// 其一：当应用程序使用广播或多播时只能使用UDP协议；其二：由于他是无连接的，所以速度快。
// 因为UDP套接口是无连接的，如果一方的数据报丢失，那另一方将无限等待，解决办法是设置一个超时。
// 建立UDP套接口时socket函数的第二个参数应该是SOCK_DGRAM，说明是建立一个UDP套接口；
// 由于UDP是无连接的，所以服务器端并不需要listen或accept函数。

namespace udp_server {

class UdpServer {
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

  bool Start() {
    SOCKET server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (server_socket == SOCKET_ERROR) {
      std::cout << "Failed to create socket!" << std::endl;
      return false;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_);
    server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr));

    const int kBufSize = 1048;
    char buf[kBufSize] = {};

    while (true) {
      memset(buf, 0, kBufSize);

      // 用来保存客户端的网络信息。
      sockaddr_in client_addr;
      memset(&client_addr, 0, sizeof(sockaddr_in));

      int client_addr_len = sizeof(sockaddr);
      // 接收客户端发来的信息,server阻塞在这里，等待client发来报文。
      int ret = recvfrom(server_socket, buf, kBufSize, 0, (sockaddr*)&client_addr, &client_addr_len);
      std::cout << "Receive msg: " << buf << " from IP:[" << inet_ntoa(client_addr.sin_addr)
                << "], Port:[" << ntohs(client_addr.sin_port) << "]" << std::endl;

      // 发送数据给客户端。
      const char* kGreeting = "Hello, I'm server!";
      sendto(server_socket, kGreeting, strlen(kGreeting), 0, (sockaddr*)&client_addr, client_addr_len);
    }

    closesocket(server_socket);
    return true;
  }

private:
  u_short port_;
};

}  // udp_server

#define PORT 6000

int main2() {
  using namespace udp_server;
  UdpServer server;
  if (!server.InitWinsock()) {
    return 1;
  }

  server.set_port(PORT);

  server.Start();

  server.ReleaseWinsock();

  return 0;
}
