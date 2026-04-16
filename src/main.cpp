#include "../include/includes.hpp"
#include "../include/server.hpp"
#include "../include/client.hpp"

int main() {
    std::cout << "tmid started.\n";
    std::string input;
    std::cin >> input;

    if (input == "s") {
        std::cout << "running TMID server...\n";
        run_server();
    } else {
        std::cout << "running TMID client...\n";
        run_client();
    }
    std::cout << "tmid terminated.\n";
}