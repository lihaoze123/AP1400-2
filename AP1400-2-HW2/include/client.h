#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <crypto.h>
#include <memory>
#include <sstream>

class Server;
#include <server.h>

class Client {
public:
	Client(std::string id, const Server& server);
	std::string get_id() const;
	std::string get_publickey() const;
	double get_wallet();
	std::string sign(std::string txt) const;

    // Creates a transaction in the server according to its inputs. To create a transaction use the specified string format described in above sections and sign the final transaction string with your private key. use both your signature and your transaction signature to create a pending transaction in the Server using add_pending_trx function.
	bool transfer_money(std::string receiver, double value);

	size_t generate_nonce();
private:
	Server const* const server;
	const std::string id;
	std::string public_key;
	std::string private_key;
};

bool operator < (const std::shared_ptr<Client>& lhs, const std::shared_ptr<Client>& rhs);

#endif //CLIENT_H
