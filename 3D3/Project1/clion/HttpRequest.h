//
// Created by rob on 12/02/18.
//

#ifndef CLION_HTTPREQUEST_H
#define CLION_HTTPREQUEST_H

#include <string>

class HttpRequest {
private:
		std::string type; //i.e. "GET"
		std::string file_path; //i.e. "/tmp/index.html"
		std::string http_ver; //i.e. "HTTP/1.0"
public:
		HttpRequest();
		std::string process_request(std::string message);
};


#endif //CLION_HTTPREQUEST_H
