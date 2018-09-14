//
// Created by rob on 12/02/18.
//

#include "HttpRequest.h"
#include <fstream>

std::string readFile (std::string request);

HttpRequest::HttpRequest() {
	type = "GET";
	file_path = ".";
	http_ver = "HTTP/1.0";
}

std::string HttpRequest::process_request(std::string message) {
	if (message.substr(0, message.find(" /")) != type ) {return "400 Bad Request";}
	file_path += message.substr(message.find("/"), message.find(" H"));
	if (message.substr(message.find("HTTP")) != http_ver) {return "505 HTTP version not supported";}
	return readFile(file_path);
}

std::string readFile (std::string request) {
	//std::string loc;
	std::string content, line;
	std::ifstream f;
	/*if (dir != ".") {
		loc = ".";
		loc += dir;
		loc += "/";
		loc += request;
		//std::cout << loc << std::endl;
	}
	else {loc = request;}
	//f.open(loc.c_str());
	//std::ifstream f("index.html");*/
	f.open(request);
	if (!f.is_open()) {return "404 Not found";}
	//std::streamsize length = f.tellg();
	//f.seekg(0, std::ios::beg);
	//std::vector<char> buffer(length);
	/*while (!f.eof()) {
		content.assign((std::istreambuf_iterator<char>(f)),(std::istreambuf_iterator<char>()));
	}*/
	/*if (f.read(buffer.data(), length)) {
		f.close();
		std::string content(buffer.begin(), buffer.end());
		std::cout << "Content: " << content << std::endl;
		return content;
	}*/
	while(!f.eof()) {
		getline(f, line);
		content += line;
		//std::cout << content << std::endl;
	}
	f.close();
	//std::cout << "Nope: " << content << std::endl;
	//return nullptr;
	return content;
}