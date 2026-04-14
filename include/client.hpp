#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include "../include/includes.hpp"

void sync(cppsocket::Socket &client) {
    
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
    auto package_header = cppheader::parse_header(raw_package_header);

    int file_count = std::stoi(package_header.get("packagesize"));
    std::clog << "recieving ["<< file_count << "] files" << std::endl;

    for (int i = 0; i < file_count; i++) {
        
        std::string raw_file_header;
        client.recv(raw_file_header);
        auto file_header = cppheader::parse_header(raw_file_header);

        std::vector<char> data;
        client.recv(data);

        // auto path = HOME / file_header.get("relativepath");
        auto path = (HOME / "Documents/TESTING_FOLDER" / file_header.get("relativepath"));
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