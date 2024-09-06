#include "server.h"

#include <iostream>

std::vector<std::string> pending_trxs;


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

void show_wallets(const Server &server) {
    // A hack way to access private member of `server`, may cause undefined behavior.
    auto clients = *((std::map<std::shared_ptr<Client>, double>*)(&server));
    
    std::cout << std::string('*', 20) << '\n';
    for (const auto& [k, v] : clients) 
        std::cout << k->get_id() << " : " << v << '\n';
    std::cout << std::string('*', 20) << '\n';
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

bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value) {
    std::replace(trx.begin(), trx.end(), '-', ' ');
    std::stringstream ss(trx);

    ss >> sender;
    if (!ss.good())
        throw std::runtime_error("Not a valid transaction!");

    ss >> receiver;
    if (!ss.good())
        throw std::runtime_error("Not a valid transaction!");

    ss >> value;
    if (!ss.eof())
        throw std::runtime_error("Not a valid transaction!");

    return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const {
    std::string sender, receiver;
    double value;

    Server::parse_trx(trx, sender, receiver, value);

    auto sender_ptr = get_client(sender),
         receiver_ptr = get_client(receiver);

    if (receiver_ptr == nullptr)
        return false;

    auto public_key = sender_ptr->get_publickey();
    auto wallet = sender_ptr->get_wallet();

    if (!crypto::verifySignature(public_key, trx, signature) || wallet < value)
        return false;
    
    pending_trxs.push_back(trx);
    return true;
}
