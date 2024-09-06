#include "client.h"

Client::Client(std::string id, const Server& server): id(id), server(&server) {
    crypto::generate_key(public_key, private_key);
}

bool operator < (const std::shared_ptr<Client>& lhs, const std::shared_ptr<Client>& rhs) {
    return lhs->get_id() < rhs->get_id();
}

std::string Client::get_id() const {
    return id;
}

std::string Client::get_publickey() const {
    return public_key;
}

double Client::get_wallet() {
    return server->get_wallet(id);
}
