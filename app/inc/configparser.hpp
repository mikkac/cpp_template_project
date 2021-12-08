#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace example {
class Configuration {
   public:
    Configuration() = default;

    int parseFile(std::string_view file_path);
    int parseCmd(int argc, char** argv);

    class Client {
        friend class Configuration;

       public:
        uint8_t getNumOfClients() const;
        std::string_view getNamePrefix() const;
        uint16_t getPort() const;

       private:
        uint8_t num_of_clients_{};
        std::string name_prefix_{};
        uint16_t port_{};
    };

    class Server {
        friend class Configuration;

       public:
        std::string_view getName() const;
        uint16_t getPort() const;

       private:
        std::string name_{};
        uint16_t port_{};
    };

    const Client& getClient() const;
    const Server& getServer() const;

   private:
    Client client_{};
    Server server_{};
};
}  // namespace example