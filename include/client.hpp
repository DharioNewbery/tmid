#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include "../include/includes.hpp"

void sync(cppsocket::Socket &client) {
    globalHeaderBuilder gHeaderConstructor;
    globalHeaderObject gHeaderObj;

    localHeaderBuilder lHeaderConstructor;
    localHeaderObject lHeaderObj;

    // send operation
    client.send(op::SYNC);

    // receive response
    std::string response;
    client.recv(response);

    if (response.compare(re::TRUE) != 0) {
        std::cout << "auth failed.\n";
        return;
    }

    // recieve package header
    std::string raw_package_header;
    client.recv(raw_package_header);
    gHeaderObj = gHeaderConstructor.deserializer(raw_package_header);

    std::clog << "recieving ["<< gHeaderObj.packagesize << "] files" << std::endl;

    for (int i = 0; i < gHeaderObj.packagesize ; i++) {
        
        std::string raw_file_header;
        client.recv(raw_file_header);
        lHeaderObj = lHeaderConstructor.deserializer(raw_file_header);
        
        std::vector<char> data;
        client.recv(data);

        // auto path = HOME / file_header.get("relativepath");
        auto path = (HOME / "Documents/TESTING_FOLDER" / lHeaderObj.relativepath );
        std::clog << "writing data to: " << path << std::endl;
        if (!cppfile::create_dirs(path.parent_path())) {
            std::cerr << "[ERROR] failed to create folder structure: " << path << std::endl;
        }
        if (!cppfile::write_to(path, data)) {
            std::cerr << "[ERROR] failed to write data to path: " << path << std::endl;
        }
    }
}

void run_client() {
    cppsocket::Socket client = cppsocket::connect("127.0.0.1", 8080);
    sync(client);
}

#endif