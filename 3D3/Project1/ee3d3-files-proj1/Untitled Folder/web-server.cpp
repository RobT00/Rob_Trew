#include "HttpRequest.h"
#include "HttpRequest.cpp"
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/select.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
//#include <dirent.h>
//#include <sys/stat.h>

#define MAX_BUFF_LEN 1024

//std::string readFile (std::string request, std::string dir);
struct sockaddr_in* findAddress (const char* name);
//void explore (char* dir_name);

int 
main(int argc, char *argv[])
{
	fd_set readFds;
	fd_set errFds;
	fd_set watchFds;
	FD_ZERO(&readFds);
	FD_ZERO(&errFds);
	FD_ZERO(&watchFds);
	HttpRequest sample;
  char server_ip[INET_ADDRSTRLEN];
  int port_num;
  struct sockaddr_in* ip_address;
	std::string directory;
	std::string response;
  if (argc < 3) {
    std::cout << "Using defaults" << std::endl;
    ip_address = findAddress("localhost");
    port_num = 40000;
		directory = ".";
		std::cout << "Directory: " << directory << std::endl;
  }
  else {
    ip_address = findAddress(argv[1]);
    //std::cout << "IP: " << server_ip << std::endl;
    if (ip_address == nullptr) {return -1;}
    //std::cout << "IP: " << server_ip << std::endl;
    port_num = atoi(argv[2]);
    std::cout << port_num << std::endl;
		directory = argv[3];
		std::cout << "Directory: " << directory << std::endl;
  }
	//explore((char*)directory.c_str());
  inet_ntop(AF_INET, &(ip_address->sin_addr), server_ip, INET_ADDRSTRLEN);
  std::cout << "IP: " << server_ip << std::endl;
	int server_sock = socket(AF_INET, SOCK_STREAM, 0); //server (listening) socket
  int dummy_sock = server_sock; //used for select()
	FD_SET(dummy_sock, &watchFds);
	int multiple = 1;
  if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &multiple, sizeof(int)) == -1) {
    perror("setsockopt");
    return -1;
  }

  struct sockaddr_in address_server;
  address_server.sin_family = AF_INET;
  //address_server.sin_port = htons(40000); //port 4000 or 40000?
  address_server.sin_port = htons(port_num); //dynamic
  std::cout << "Port: " << port_num << std::endl;
  //address_server.sin_addr.s_addr = inet_addr("127.0.0.1"); //localhost
  address_server.sin_addr.s_addr = inet_addr(server_ip); //dynamic
  std::cout << "IP: " << server_ip << std::endl;
  memset(address_server.sin_zero, '\0', sizeof(address_server.sin_zero));

  if (bind(server_sock, (struct sockaddr*)&address_server, sizeof((address_server))) == -1) {
    perror("bind");
    return -1;
  }

  if (listen(server_sock, SOMAXCONN) == -1) { //no limit
    perror("listen");
    return -1;
  }

	/*fd_set master;
	FD_ZERO(&master);
	FD_SET(server_sock, &master);*/
	//int socketCount = 0;
	struct timeval _t;
	std::stringstream string_s;
	for (;;) {
		int socketCount = 0;
		readFds = watchFds;
		errFds = watchFds;
		_t.tv_sec = 30;
		_t.tv_usec = 0;
		//fd_set copy = master;
		if ((socketCount = select(dummy_sock + 1, &readFds, nullptr, &errFds, &_t)) == -1) {
			std::cout << "Error finding client" << std::endl;
			return -1;
		}
		if (socketCount == 0) {
			//std::cout << "No received data for 3 secs" << std::endl;
			std::cout << "Server is still running" << std::endl;
			std::cout << "If you wish to stop, connect a client and send 'STOP'" << std::endl;
		}
		else {
			for (int sending_sock = 0; sending_sock <= dummy_sock; sending_sock++) {
				//std::cout <<"loop"<< std::endl;
				if (FD_ISSET(sending_sock, &readFds)) {
					if (sending_sock == server_sock) {
						struct sockaddr_in address_client;
						socklen_t clientAddressSize = sizeof(address_client);
						int client_sock = accept(server_sock, (struct sockaddr *) &address_client, &clientAddressSize);
						if (client_sock == -1) {
							perror("accept");
							return -1;
						}
						char client_ip[INET_ADDRSTRLEN] = {'\0'};
						inet_ntop(address_client.sin_family, &address_client.sin_addr, client_ip, sizeof(client_ip));
						std::cout << "Connection made from: " << client_ip << ":" <<
											ntohs(address_client.sin_port) << " with Socket ID: " << client_sock << std::endl;
						if (dummy_sock < client_sock) { dummy_sock = client_sock; }
						FD_SET (client_sock, &watchFds);
					}
					else {
						char buff[MAX_BUFF_LEN];
						memset(buff, '\0', sizeof(buff));
						int recvLen = 0;
						if ((recvLen = recv(sending_sock, buff, MAX_BUFF_LEN, 0)) == -1) {
							std::cout << "Error receiving" << std::endl;
							return -1;
						}
						std::cout << recvLen << std::endl;
						std::cout << "Message: " << buff << std::endl;
						std::string output(buff);
						//output = "GET /tmp/index.html HTTP/1.0";
						if (output == "STOP") {
							std::cout << "Stopping Server" << std::endl;
							for (sending_sock = 0; sending_sock <= dummy_sock; sending_sock++)  {
								if (FD_ISSET(sending_sock, &readFds)) { //Make this work nicely?
									//send(sending_sock, "Stopping Server", strlen("Stopping Server"), 0); //Possible newline?
									send(sending_sock, "close", strlen("close"), 0);
									close(sending_sock);
									FD_CLR(sending_sock, &watchFds);
								}
							}
							std::cout << "END" << std::endl;
							close (server_sock);
							return 0;
						}
						if (output == "close" || recvLen == 0) {
							send(sending_sock, "close", strlen("close"), 0);
							close(sending_sock);
							FD_CLR(sending_sock, &watchFds);
						} else {
							std::cout << "Socket " << sending_sock << " receives: " << buff << std::endl;
							//response = readFile("index.html", directory);
							response = sample.process_request(output);
							if (send(sending_sock, response.c_str(), response.length(), 0) == -1) {
								std::cout << "Sending error" << std::endl;
								return -1;
							}
						}
					}
				}
			}
		}
	}
  /*struct sockaddr_in address_client;
  socklen_t clientAddressSize = sizeof(address_client);
  int client_sock = accept(server_sock, (struct sockaddr*)&address_client, &clientAddressSize);
  /*if (accept(server_sock, (struct sockaddr*)&address_client, &clientAddressSize) == -1) {
    perror("accept");
    return -1;
  }
  if (client_sock == -1) {
    perror("accept");
    return -1;
  }

  char client_ip[INET_ADDRSTRLEN] = {'\0'};
  /*char* buff;
  int buff_len = 20;
  buff = new char[buff_len];
  buff = {'\0'};
  char buff[MAX_BUFF_LEN] = {0};
  std::stringstream string_s;
  std::cout << "HERE\n" << std::endl;
  for (;;) {
    inet_ntop(address_client.sin_family, &address_client.sin_addr, client_ip, sizeof(client_ip));
    std::cout << client_ip << " connected to server on: " << ntohs(address_client.sin_port) << std::endl;
    memset(buff, '\0', sizeof(buff));
    //buff = {'\0'};
    if (recv(client_sock, buff, MAX_BUFF_LEN, 0) == -1) {
      perror("recv");
      return -1;
    }
    std::cout << "Request: ";
    string_s << buff << std::endl;
    std::cout << buff << std::endl;

    if (string_s.str() == "close\n") {
      send(client_sock, "close", strlen("close"), 0);
      close(client_sock);
      break;
    }

    if (send(client_sock, "test", strlen("test"), 0) == -1) {
      perror("send");
      return -1;
    }

    string_s.str("");
  }*/

  //delete [] buff;
  std::cout << "END" << std::endl;
  close (server_sock);
	return 0;
}
//request should be sent as "GET server/file.type HTTP/1.0"


struct sockaddr_in* findAddress (const char* name) {
  struct addrinfo hints;
  struct addrinfo *res;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET; //Trinity only uses IPv4
  hints.ai_socktype = SOCK_STREAM;

  int found = 0;
  if ((found = getaddrinfo(name, "80", &hints, &res)) != 0) {
    std::cout << "Could not resolve IP: " << name << std::endl;
    //server_ip = '\0';
    return NULL;
  }
  /*struct sockaddr_in* ip = (struct sockaddr_in*)res->ai_addr;
  char ip_str[INET_ADDRSTRLEN];
  inet_ntop (AF_INET, &(ip->sin_addr), ip_str, INET_ADDRSTRLEN);
  std::cout << "IP(pfn): " << ip_str << std::endl;
  return ip_str;*/
  return ((struct sockaddr_in*)res->ai_addr);
}

/*void explore (char* dir_name) {
	DIR *dir;
	struct dirent *entry;
	struct stat info;

	//1 open
	dir = opendir(dir_name);
	if (!dir) {
		std::cout << "Dir: " << dir_name << " not found" << std::endl;
		return;
	}
	//2 read
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] != '.') {
			std::string path = std::string(dir_name) + "/" + std::string(entry->d_name);
			std::cout << "Entry = " << path << std::endl;
			stat(path.c_str(), &info);
			if (S_ISDIR(info.st_mode)) {
				explore((char*)path.c_str());
			}
		}
	}
	//3 close
	closedir(dir);
}*/
//socket
//bind
//listen
//accept (wait for connection)
//(establish connection)
//receive (request)
//(process)
//send (response)
//close connection (if received)