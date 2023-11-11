#include <iostream>  
#include <cstring>  
#include <sys/socket.h>  
#include <netdb.h>
#include <arpa/inet.h>  
#include <unistd.h>  
hostent *host;
int main() {  
    int sock = 0, valread;  
    struct sockaddr_in serv_addr;  
    char buffer[1024] = {0};  
    const char* message = "shutdown";  
  
    // 创建socket文件描述符  
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
  
    // 设置目标服务器地址和端口号  
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_port = htons(2000);  
    host = gethostbyname("betteroier.site");
    serv_addr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)host->h_addr_list[0]));
    /* if (inet_pton(AF_INET, "betteroier.site", &serv_addr.sin_addr) <= 0) {  
        perror("inet_pton failed");  
        exit(EXIT_FAILURE);  
    }   */
  
    // 连接到目标服务器  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {  
        perror("connect failed");  
        exit(EXIT_FAILURE);  
    }  
  
    // 向目标服务器发送消息  
    if (send(sock, message, strlen(message), 0) < 0) {  
        perror("send failed");  
        exit(EXIT_FAILURE);  
    }  
  
    // 从目标服务器接收消息并输出到控制台  
    valread = read(sock, buffer, 1024);  
    std::cout << "Received message: " << buffer << std::endl;  
  
    close(sock);  // 关闭连接  
    return 0;  
}