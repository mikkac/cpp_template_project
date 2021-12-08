#include <iostream>
#include <thread>
#include <vector>

#include "client.hpp"
#include "configparser.hpp"
#include "server.hpp"
#include "spdlog/spdlog.h"

int main(int argc, char** argv) {
    example::Configuration config;
    int parsing_result{};
    if (argc > 1) {
        spdlog::info("Parameters will be loaded from CMD");
        parsing_result = config.parseCmd(argc, argv);
    } else {
        spdlog::info("Parameters will be loaded from config file");
        parsing_result = config.parseFile("config.toml");
    }

    if (parsing_result) return parsing_result;

    auto server = std::thread([&config]() {
        example::runServer(config.getServer().getName(),
                           config.getServer().getPort());
    });

    std::vector<std::thread> clients;
    for (uint i{}; i < config.getClient().getNumOfClients(); ++i) {
        clients.push_back(std::thread([&config, &i]() {
            example::runClient(
                fmt::format("{}{}", config.getClient().getNamePrefix(), i),
                config.getClient().getPort());
        }));
    }

    for (auto& client : clients) {
        client.join();
    }
    server.join();  // This will never happen, but who cares - it's just an
                    // example

    return 0;
}