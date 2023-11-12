#include <iostream>
#include <cstdlib>  
#include <cstring>  
#include <unistd.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
 
int main()
{
    int server_fd, new_socket;  
    struct sockaddr_in address;  
    int opt = 1;  
    int addrlen = sizeof(address);  
    char buffer[1024] = {0};  
    const char* message = "shutdown";  
    const char* message1 = "Received";  
  
    // 创建socket文件描述符  
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
  
    // 设置socket选项  
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {  
        perror("setsockopt failed");  
        exit(EXIT_FAILURE);  
    }  
  
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = inet_addr("192.168.0.108");  
    address.sin_port = htons(2000);  
  
    // 绑定socket到本地地址和端口号  
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
  
    // 监听连接，等待客户端发送消息  
    if (listen(server_fd, SOMAXCONN) < 0) {  
        perror("listen failed");  
        exit(EXIT_FAILURE);  
    }  
	while (true)
	{
		//接受连接请求
		std::cout << "wait accept...." << std::endl;
		int s_accept = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
		if (s_accept < 0) {
			perror("accept failed");  
            exit(EXIT_FAILURE);
		}
		std::cout << "Connection established Successfully" << std::endl;
		while (true)
		{
			std::cout << "Waiting for Client Data...." << std::endl;
			int recv_len = recv(s_accept, buffer, sizeof(buffer), 0);
			if (recv_len < 0) {
				std::cout << "Error: receive info from server failed !" << std::endl;
				return -1;
			}else if (recv_len==0){
                std::cout << "Client Off!" << std::endl;
                break;
            }
			std::cout << "Client Data:" << buffer << std::endl;
			if(memcmp(buffer,message,strlen(message))==0){
                int sendLen = send(s_accept, (char*)message1, sizeof(message1), 0);
			    if (sendLen < 0) {
				    std::cout << "Error: send info to server failed !" << std::endl;
			    }else if (sendLen == 0){
                    std::cout << "Client Off!" << std::endl;
                    break;
                }
			    std::cout << "Closing confirmed!" << std::endl;
                system("shutdown -h now");
            }
		}
		
	}
}
 
