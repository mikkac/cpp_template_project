#include <iostream>
#include <thread>
#include <vector>

#include "CLI/App.hpp"
#include "CLI/Config.hpp"
#include "CLI/Formatter.hpp"
#include "client.hpp"
#include "server.hpp"
#include "spdlog/spdlog.h"
// #define FMT_HEADER_ONLY
// #include "fmt/format.h"

int main(int argc, char** argv) {
    CLI::App app(
        "Example application using great libraries fetched with conan. If no "
        "cmd params are given, TOML config is read from main repo directory");
    int server_port{5555};
    int client_port{5555};
    uint client_num{3};
    app.add_option<int>("-s, --server-port", server_port,
                        "Port used by the server");
    app.add_option<int>("-c, --client-port", client_port,
                        "Port used by the clients");
    app.add_option<uint>("-n, --client-num", client_num,
                         "Number of spawned clients");

    if (argc > 1) {
        spdlog::info("Parameters will be loaded from CMD");
        CLI11_PARSE(app, argc, argv)
    } else {
        spdlog::info("Parameters will be loaded from config file");
        // parseConfig("../../config.toml");
    }

    auto server = std::thread(
        [&server_port]() { example::runServer("Server", server_port); });

    std::vector<std::thread> clients;
    for (uint i{}; i < client_num; ++i) {
        clients.push_back(std::thread([&client_port, &i]() {
            example::runClient(fmt::format("Client_{}", i), client_port);
        }));
    }

    for (auto& client : clients) {
        client.join();
    }
    server.join();  // This will never happen, but who cares - it's just an
                    // example

    return 0;
}