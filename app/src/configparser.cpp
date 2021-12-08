#include "configparser.hpp"

#include "CLI/App.hpp"
#include "CLI/Config.hpp"
#include "CLI/Formatter.hpp"
#include "spdlog/spdlog.h"
#include "toml.hpp"

namespace example {

int Configuration::parseFile(std::string_view file_path) {
    using namespace std::literals;
    try {
        auto config = toml::parse_file(file_path);

        client_.num_of_clients_ =
            config["client"]["num_of_clients"].value_or(1);
        client_.name_prefix_ =
            config["client"]["name_prefix"].value_or("unknown_"sv);
        client_.port_ = config["client"]["port"].value_or(5555);

        server_.name_ = config["server"]["name"].value_or("unknown"sv);
        server_.port_ = config["server"]["port"].value_or(5555);

        spdlog::info(toml::json_formatter{config});
    } catch (const std::exception& e) {
        spdlog::error(e.what());
        return 1;
    }
    return 0;
}

int Configuration::parseCmd(int argc, char** argv) {
    CLI::App app(
        "Example application using great libraries fetched with conan. If no "
        "cmd params are given, TOML config is read from main repo directory");

    app.add_option<uint8_t>("-n, --client-num", client_.num_of_clients_,
                            "Number of spawned clients");
    app.add_option<std::string>("--client-name", client_.name_prefix_,
                                "Name prefix of spawned clients");
    app.add_option<uint16_t>("-c, --client-port", client_.port_,
                             "Port used by the clients");

    app.add_option<std::string>("--server-name", server_.name_,
                                "Name of the server");
    app.add_option<uint16_t>("-s, --server-port", server_.port_,
                             "Port used by the server");

    CLI11_PARSE(app, argc, argv)  // This returns !=0 on error
    return 0;
}

uint8_t Configuration::Client::getNumOfClients() const {
    return num_of_clients_;
}
std::string_view Configuration::Client::getNamePrefix() const {
    return name_prefix_;
}

uint16_t Configuration::Client::getPort() const { return port_; }

std::string_view Configuration::Server::getName() const { return name_; }

uint16_t Configuration::Server::getPort() const { return port_; }

const Configuration::Client& Configuration::getClient() const {
    return client_;
}
const Configuration::Server& Configuration::getServer() const {
    return server_;
}

}  // namespace example