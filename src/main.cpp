#include "../include/includes.hpp"
#include "../include/server.hpp"
#include "../include/client.hpp"

int main() {
    std::string input;
    std::cin >> input;

    if (input == "s") {
        run_server();
    } else {
        run_client();
    }
}