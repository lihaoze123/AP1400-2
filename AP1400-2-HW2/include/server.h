#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <map>
#include <string>
#include <random>
#include <sstream>
#include <iomanip>

class Client;
#include <client.h>

class Server {
public:
	Server() = default;

    // This function will create a new Client with the specified id. If this id already exists, the server should add a random 4 digit number at the end of it automatically.
	std::shared_ptr<Client> add_client(std::string id);

    // Using this function you can get a pointer to a Client using its id.
	std::shared_ptr<Client> get_client(std::string id) const;

    // Using this function will return the wallet value of the client with username id.
	double get_wallet(std::string id) const;

	bool parse_trx(std::string trx, std::string sender, std::string receiver, double value);
	bool add_pending_trx(std::string trx, std::string signature);
	size_t mine();
private:
	std::map<std::shared_ptr<Client>, double> clients;
};


std::string random_str(size_t w);

#endif //SERVER_H
