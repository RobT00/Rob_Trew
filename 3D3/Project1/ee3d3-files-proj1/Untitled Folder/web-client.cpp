#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include <netinet/ip.h> // superset of inet.h and socket.h

#include <iostream>
#include <sstream>

struct sockaddr_in* findAddress (const char* name);
using namespace std;

int main(int argc, char *argv[]) {
	cout << "TEST" << endl;
  char ipAddress[INET_ADDRSTRLEN];
	struct sockaddr_in *server_ip;
  int port;
    //if(argc < 2) {
		server_ip = findAddress("localhost");
		port = 40000;
    //}
   /* else {
    string address(argv[1]);
			cout << address << endl;
			address.erase(0, address.find("//") + 2);
    string ip = address.substr(0, address.find(":"));
		cout << ip << endl;
    server_ip ipAddress = findAddress(ip.c_str());
    string prt = address.substr(address.find(":") + 1, address.find("/") - 1);
    port = atoi(prt.c_str());
    size_t pos = address.find("index");
    string file = address.substr(pos);
    string message;
		message = "GET";
	 	message += file;
		message += "HTTP/1.0";
		message += "\r\n\r\n";

    }*/
    
  inet_ntop(AF_INET, &(server_ip->sin_addr), ipAddress, INET_ADDRSTRLEN);
    cout << "IP: " << ipAddress << endl;
    int buffSize =10000;
    char buf[buffSize];             // buffer to allow for reading in of user message
    string userMess;                // string to store user message
    int sendMess;                   // used to send user message to server
    int bytesRec;                   // bytes received by server from client
    
    // CREATE SOCKET 
    int server_sock = socket(AF_INET, SOCK_STREAM, 0); // socket for listening server

    // FILL IN HINT STRUCTURE
    struct sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    hint.sin_addr.s_addr = inet_addr(ipAddress);
    memset(hint.sin_zero, '\0', sizeof(hint.sin_zero));

    // CONNECT TO SERVER 
    int connValid = connect(server_sock, (struct sockaddr*)&hint, sizeof(hint));
    if(connValid == -1){
        perror("server");
        close(server_sock);
        return 2;
    }

    cout << "Connection made..." << endl;

    // DO - WHILE LOOP TO SEND AND RECIEVE DATA
   do{
        // prompt for text
        //cout << ">> ";
        //getline(cin, userMess);

        // send text to server
        sendMess = send(server_sock, "GET/index.htmlHTTP/1.0",  20, 0);
        if(sendMess != -1){
            // wait for response 
            memset(buf, 0, buffSize);
            bytesRec = recv(server_sock, buf, buffSize, 0);
            if(bytesRec > 0){
                // echo response
                cout << "SERVER>> " << string(buf, 0, bytesRec) << endl; 
            } 
        }
    } while(userMess != "STOP" );

    cout << "Terminating connection..." << endl;

    // CLOSE DOWN CONNECTIONS 
    close(server_sock);
}

  struct sockaddr_in* findAddress (const char* name) {
  struct addrinfo base;
  struct addrinfo *res;

  memset(&base, 0, sizeof(base));
  base.ai_family = AF_INET;
  base.ai_socktype = SOCK_STREAM;

  int found = 0;
  if ((found = getaddrinfo(name, "80", &base, &res)) != 0) {
    std::cout << "Could not resolve IP: " << name << std::endl;
    //server_ip = '\0';
    return NULL;
  }
  return ((struct sockaddr_in*)res->ai_addr);
}