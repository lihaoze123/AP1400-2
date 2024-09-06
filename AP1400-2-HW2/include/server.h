#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <map>
#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <algorithm>

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

    // Each transaction has 3 properties: i) id of the sender ii) id of the receiver iii) value of money to transfer. We will show each transaction with a string, concatenating each of these properties with a -. For example if ali sends 1.5 coins to hamed the transaction will be shown by a string "ali-hamed-1.5". This function will parse this string format and outputting each property separately, if the string is not standard you should throw a runtime error.
	static bool parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value);

    // Each Client can add a pending transaction using the transaction format described in the above section. Only accept a pending transaction by authenticating the sender's signature and if he has enough money in his wallet.
	bool add_pending_trx(std::string trx, std::string signature) const;

	size_t mine();
private:
	std::map<std::shared_ptr<Client>, double> clients;
};

extern std::vector<std::string> pending_trxs;

std::string random_str(size_t w);
void show_wallets(const Server& server);

#endif //SERVER_H
