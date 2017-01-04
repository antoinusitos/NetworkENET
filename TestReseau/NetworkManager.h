#pragma once

#include <thread>
#include <enet/enet.h>

class Client;

class NetworkManager
{
public:
	NetworkManager(Client* theOwner);
	~NetworkManager();

	void InitializeNetwork();

	void JoinThreads();

	void HandlesEvent();

	void SendText(std::string text);

private:
	ENetHost* _client;

	std::thread* _eventThread;

	Client* _owner;
};

