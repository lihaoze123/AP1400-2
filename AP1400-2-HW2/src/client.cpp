#include "client.h"

Client::Client(std::string id, const Server& server) : id(id), server(&server) {}

bool operator < (const std::shared_ptr<Client>& lhs, const std::shared_ptr<Client>& rhs) {
    return lhs->get_id() < rhs->get_id();
}

std::string Client::get_id() const {
    return id;
}

double Client::get_wallet() {
    return server->get_wallet(id);
}
