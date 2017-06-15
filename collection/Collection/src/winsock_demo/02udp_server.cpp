#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

// 1.TCP���������ӵģ�����ͨ��֮ǰ��Ҫ��������������ȷ��˫���Ƿ��Ѿ�׼�����ˡ�
// ��ˣ�˫������������Ǵ��������ġ�
// ��UDP���������ݰ��ģ���˾ͺ���Ŀ��һ����������ڿ����дһ��ֽ�����������������
// ��ַ����Ϣ�����֮�󣬽����߲�֪���ö�������˭�Ĺ����ġ�
// ��UDP���շ�����recvform��sendto��sockaddr�ṹ�ĵ�ַ�����ڱ�������﷢���ĺͷ��͵�����ĵ�ַ��Ϣ��

// 2.UDP�׽ӿ��������ӵġ����ɿ������ݱ�Э�飻��Ȼ�����ɿ�Ϊʲô��Ҫ���أ�
// ��һ����Ӧ�ó���ʹ�ù㲥��ಥʱֻ��ʹ��UDPЭ�飻������������������ӵģ������ٶȿ졣
// ��ΪUDP�׽ӿ��������ӵģ����һ�������ݱ���ʧ������һ�������޵ȴ�������취������һ����ʱ��
// ����UDP�׽ӿ�ʱsocket�����ĵڶ�������Ӧ����SOCK_DGRAM��˵���ǽ���һ��UDP�׽ӿڣ�
// ����UDP�������ӵģ����Է������˲�����Ҫlisten��accept������

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

      // ��������ͻ��˵�������Ϣ��
      sockaddr_in client_addr;
      memset(&client_addr, 0, sizeof(sockaddr_in));

      int client_addr_len = sizeof(sockaddr);
      // ���տͻ��˷�������Ϣ,server����������ȴ�client�������ġ�
      int ret = recvfrom(server_socket, buf, kBufSize, 0, (sockaddr*)&client_addr, &client_addr_len);
      std::cout << "Receive msg: " << buf << " from IP:[" << inet_ntoa(client_addr.sin_addr)
                << "], Port:[" << ntohs(client_addr.sin_port) << "]" << std::endl;

      // �������ݸ��ͻ��ˡ�
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
