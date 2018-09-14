//Robert Trew
#include <string>
#include <thread>
#include <iostream>
#include <Windows.h>
#include <stdio.h>

using std::string;

#pragma comment(lib,"ws2_32.lib")

HINSTANCE hInst;
WSADATA wsaData;
void mParseURL (char *mURL, string &serverName, string &filePath, string &fileName);
SOCKET connectToWebClient (char *szServerName, WORD portNum);
int getHeaderLength (char* content);
char *readURL (char *szURL, long &bytesReturnedOut, char **headerOut);

int main()
{
  //std::cerr << "web server is not implemented yet" << std::endl;
	const int bufLen = 124;
	char *szURL = "http://stackoverflow.com";
	long fileSize;
	char *memBuffer, *headerBuffer;
	FILE *fp;
	memBuffer = headerBuffer = NULL;
	if (WSAStartup(0x101, &wsaData) != 0) { return -1; }
	memBuffer = readURL(szURL, fileSize, &headerBuffer);
	printf("returned from readURL\n");
	printf("data returned:\n%s", memBuffer);
	if (fileSize != 0) {
		printf("Got some data\n");
		fp = fopen("downloaded.file", "wb");
		fwrite(memBuffer, 1, fileSize, fp);
		fclose(fp);
		delete(memBuffer);
		delete(headerBuffer);
	}
	WSACleanup();
	return 0;
}

void mParseURL(char *mURL, string &serverName, string &filePath, string &fileName) {
	string::size_type n;
	string URL = mURL;
	if (URL.substr(0, 7) == "http://") { URL.erase(0, 7); }
	if (URL.substr(0, 8) == "https://") { URL.erase(0, 8); }
	n = URL.find('/');
	if (n != string::npos) {
		serverName = URL.substr(0, n);
		filePath = URL.substr(n);
		n = filePath.rfind('/');
		fileName = filePath.substr(n + 1);
	}
	else {
		serverName = URL;
		filePath = "/";
		fileName = "";
	}
}

SOCKET connectToWebClient(char *szServerName, WORD portNum) {
	struct histent *hp;
	unsigned int addr;
	struct sockaddr_in server;
	SOCKET conn;
	conn = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (conn == INVALID_SOCKET) { return NULL; }
	if (inet_addr(szServerName) == INADDR_NONE) {
		hp = gethostbyname(szServerName);
	}
	else {
		addr = inet_addr(szServerName);
		hp = gethostbyaddr((char*)&addr, sizeof(addr), AF_INET);
	}
	if (!hp) {
		closesocket(conn);
		return NULL;
	}
	server.sin_addr.s_addr = *((unsigned long*)hp->h_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(portNum);
	if (connect(conn, (struct sockaddr*)&server, sizeof(server))) {
		closesocket(conn);
		return NULL;
	}
	return conn;
}


