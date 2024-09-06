#include "server.h"

#include <iostream>

std::string random_str(size_t w) {
    int upper_bound = 1, ww = w;
    while (ww --)
        upper_bound *= 10;
    upper_bound -= 1;

    std::random_device id;
    std::mt19937 gen(id());
    std::uniform_int_distribution<> distrib(0, upper_bound);

    std::stringstream ss;
    ss << std::setw(w) << std::setfill('0');
    ss << distrib(gen);

    std::string res;
    ss >> res;

    return res;
}

std::shared_ptr<Client> Server::get_client(std::string id) const {
    Client cmp{id, Server{}};
    auto lower_bound = clients.lower_bound(std::make_shared<Client>(cmp));

    if (lower_bound == clients.end())
        return nullptr;

    auto matched = lower_bound->first;

    if (matched->get_id() == id)
        return matched;
    else 
        return nullptr;
}

std::shared_ptr<Client> Server::add_client(std::string id) {
    if (Server::get_client(id) != nullptr) 
        id += random_str(4);

    Client client{id, *this};

    auto res = std::make_shared<Client>(client);
    clients[res] = 5;

    return res;
}

double Server::get_wallet(std::string id) const {
    auto client = get_client(id);

    if (client == nullptr)
        return 0;
    else 
        return clients.at(client);
}
