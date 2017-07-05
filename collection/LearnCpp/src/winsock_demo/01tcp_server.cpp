#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>

#include <winsock2.h>  // ��������ͨ��ͷ�ļ�

#pragma comment(lib, "ws2_32.lib")  // ���������ӵ�ʱ�򽫸ÿ����ӽ�ȥ����ʽ���ض�̬�⡣���� ws2_32.dll��

// ��̬���ӿ������ּ��ط�ʽ����ʽ���غ���ʾ���ء�
// 1.��ʽ�����ֽ�����ʱ���أ�ָ�������������ڴ�ʱ����DLL������DLL�����ڴ档��ʽ����Ҳ���о�̬���ӿ�����⣬��������Դ󣬼���ʱ��ͻ�������û����ܽ��ܡ�
// .lib �ļ�����DLL�����ĺ����ͱ����ķ�������ֻ������Ϊ���ӳ����ṩ��Ҫ����Ϣ���Ա�������ʱ�ҵ��������������ڵ�ַ��
// .dll �ļ��Ű���ʵ�ʵĺ��������ݡ�����������Ҫ�� dllDemo.lib ���뵽��ǰ��Ŀ.
// 2.��ʽ�����ֽ�����ʱ���أ�ָ�����������й�������ҪDLL�еĺ���ʱ�ټ��ء���ʽ�����ǽ��ϴ�ĳ���ֿ����صģ���������ʱֻ��Ҫ�������������ڴ棬������ٶȿ죬�û�����á�

// ��̬���ӿ�ĺô�������Ҫ��ʱ����ض�̬���ӿ�ĳ��������
// ��ʽ���ӵ�ȱ�㣺ʹ�ñȽϼ򵥣��ڳ�����������ֿ�������ʹ�ú��������ǵ��������ʮ����dll��̬���ӿ��ʱ�򣬴�ʱ�����ʹ����ʽ���ӵ�ʱ��
// �����˳����ʱ����ʮ������̬���ӿⶼ��Ҫ���ص��ڴ棬ӳ�䵽�ڴ�ĵ�ַ�ռ䣬��ͻ�Ӵ���̵�����ʱ�䣬���ҳ������й����У�ֻ����ĳ��������ʹ��ĳ��������
// ���ʹ����ʽ���ӻ������Դ���˷ѡ�������Ҫ���ö�̬���صķ�ʽ��

#define PORT 8888
#define  BUFFER_SIZE 256

static const std::string kExitFlag = "-1";

// �ο���http://c.biancheng.net/cpp/html/3030.html

int mains1() {
  // ��ʼ��socket dll��
  // WinSock �淶�����°汾��Ϊ 2.2��
  // //���汾��Ϊ2�����汾��Ϊ2������ 0x0202��
  // WSADATA����Dll����Ϣ��
  WORD winsock_version = MAKEWORD(2,2);
  WSADATA wsa_data;
  if (WSAStartup(winsock_version, &wsa_data) != 0) {
    std::cout << "Failed to init socket dll!" << std::endl;
    return 1;
  }

  // ���� AF_INET ��ʾʹ�� IPv4 ��ַ��SOCK_STREAM ��ʾʹ���������ӵ����ݴ��䷽ʽ��IPPROTO_TCP ��ʾʹ�� TCP Э�顣
  // AF �ǡ�Address Family���ļ�д��INET�ǡ�Inetnet���ļ�д��AF_INET ��ʾ IPv4 ��ַ������ 127.0.0.1��AF_INET6 ��ʾ IPv6 ��ַ������ 1030::C9B4:FF12:48AA:1A2B��
  // �ݴ��䷽ʽ�����õ������֣�SOCK_STREAM �� SOCK_DGRAM�� SOCK_STREAM ��ʾ�������ӵ����ݴ��䷽ʽ�� SOCK_DGRAM ��ʾ�����ӵ����ݴ��䷽ʽ��
  //  protocol ��ʾ����Э�飬���õ��� IPPROTO_TCP �� IPPTOTO_UDP���ֱ��ʾ TCP ����Э��� UDP ����Э�顣
  SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (server_socket == INVALID_SOCKET) {
    std::cout << "Failed to create server socket!" << std::endl;
    return 2;
  }

  // ��IP�Ͷ˿ڡ�
  // IP��ַ�Ͷ˿ڶ������� sockaddr_in �ṹ���С�
  //struct sockaddr_in {
  //  sa_family_t     sin_family;   //��ַ�壨Address Family����Ҳ���ǵ�ַ����
  //  uint16_t        sin_port;     //16λ�Ķ˿ں�
  //  struct in_addr  sin_addr;     //32λIP��ַ
  //  char            sin_zero[8];  //��ʹ�ã�һ����0���
  //};

  //struct in_addr {
  //  in_addr_t  s_addr;  //32λ��IP��ַ
  //};

  //struct sockaddr {
  //  sa_family_t  sin_family;   //��ַ�壨Address Family����Ҳ���ǵ�ַ����
  //  char         sa_data[14];  //IP��ַ�Ͷ˿ں�
  //};

  sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.S_un.S_addr = INADDR_ANY;

  // Ϊʲôʹ�� sockaddr_in ����ʹ�� sockaddr.
  // sockaddr ��һ��ͨ�õĽṹ�壬������������������͵�IP��ַ�Ͷ˿ںţ��� sockaddr_in ��ר���������� IPv4 ��ַ�Ľṹ�塣
  // ��������ͨ�ýṹ�� sockaddr ʹ�ò��㣬����Բ�ͬ�ĵ�ַ���Ͷ����˲�ͬ�Ľṹ�塣
  if (bind(server_socket, (LPSOCKADDR)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
    std::cout << "Failed to bind port!" << std::endl;
    return 3;
  }

  // ������
  // �ڶ��������� ������еĳ��ȡ�
  // listen() ֻ�����׽��ֽ������״̬����û���������տͻ�������listen() ����Ĵ�������ִ�У�ֱ������ accept()��
  // accept() ����������ִ�У�������벻�ܱ�ִ�У���ֱ�����µ���������
  if (listen(server_socket, 10)) {
    std::cout << "Failed to listen!" << std::endl;
    return 4;
  }

  // ѭ���������ݡ�
  sockaddr_in client_addr;
  int client_addr_len = sizeof(client_addr);
  std::cout << "Wait for connecting..." << std::endl;

  // ����һ��ִ�е� accept() �ͻᱻ��������ͣ���У���ֱ���ͻ��˷�������
  SOCKET client_socket = accept(server_socket, (SOCKADDR*)&client_addr, &client_addr_len);
  if (client_socket == INVALID_SOCKET) {
    std::cout << "Failed to accept!" << std::endl;
    return 5;
  }

  std::cout << "Succeed to receive a connection: " << inet_ntoa(client_addr.sin_addr) << std::endl;

  char recv_buf[BUFFER_SIZE] = {};
  while (true) {
    // �������ݡ�
    // ����ֵ�Ƕ�ȡ���ֽ�����û������ʱ���ȴ�����
    int ret = recv(client_socket, recv_buf, BUFFER_SIZE, 0);
    if (ret < 0) {
      std::cout << "Failed to receive data!" << std::endl;
      break;
    }

    std::cout << "Receive from Client: " << recv_buf << std::endl;
    if (kExitFlag == recv_buf) {
      std::cout << "Exit!" << std::endl;
      break;
    }

    // �������ݸ��ͻ��ˡ�
    char* send_data = "Hello, Tcp Client!\n";
    send(client_socket, send_data, strlen(send_data), 0);
  }

  // �ر��׽��֡�
  closesocket(client_socket);
  closesocket(server_socket);

  // �ͷ�dll��
  WSACleanup();

  return 0;
}