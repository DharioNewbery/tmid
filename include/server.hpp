#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include "../include/includes.hpp"

void create_group(const std::string &group_alias) {
    /* Ensure if a group of same name doesnt exist */
    auto target = GROUPS_FOLDER / group_alias;
    
    if (cppfile::exists(target)) {
        std::cout << "Two groups cannot have the same alias. '" << group_alias << "'\n";
    }

    cppfile::create_dir(target);

    cppfile::write_to(target / GROUP_CONFIG_FILENAME, GROUP_CONFIG_TEMPLATE.as<std::string>());
}

// send TRUE (TESTING)
bool authenticate_client(cppsocket::Socket& client) {
    std::cout << "Authenticating user...\n";
    client.send(re::TRUE);
    std::cout << "user authenticated!\n";
    return true;
}

// send package size
// loop: send file's header, send file's data
void sync_client(cppsocket::Socket& client) {

    std::cout << "Synchronizing user...\n";

    /* FOR TEST: THIS CAN BE CHANGED TO ANY PATH IN COMPUTER */
    auto target_folder = fs::current_path().parent_path(); 

    auto files = cppfile::get_path_tree_from(target_folder);

    // prepare and send package header
    cppheader::Header package_header {"packagesize"};
    package_header.set("packagesize", std::to_string(files.size()));

    std::clog << "total number of files: " << files.size() << std::endl;
    client.send(package_header.to_string());

    // prepare and send individual files
    cppheader::Header file_header {"relativepath"};
    for (auto file: files) {
        // send header
        file_header.set("relativepath", file);
        client.send(file_header.to_string());

        // send data
        std::vector<char> data;
        auto path = target_folder.parent_path() / file;
        std::clog << "reading data from: " << path << std::endl;
        cppfile::read_from(path, data);
        client.send(data);
    }

    std::cout << "user Synchronized\n";

}

void run_server() {
    // create server
    cppsocket::Acceptor acceptor(8080);

    bool isRunning = true;
    while (isRunning) {
        // listen and accept connection
        auto client = acceptor.accept();

        // get operation
        std::string operation;
        client.recv(operation);

        // resolve operation
        if (operation == op::SYNC)
            if (authenticate_client(client))
            sync_client(client);
    }
}

#endif