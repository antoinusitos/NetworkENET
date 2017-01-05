#pragma once

#include <thread>
#include <memory>
#include <enet/enet.h>
#include <mutex>

class Client;

class NetworkManager
{
public:
	NetworkManager(Client* theOwner);
	~NetworkManager();

	bool Init();

	void Shutdown();

	void SendText(const std::string& text);

private:

	void HandlesEvent();

	ENetHost* _client;

	std::unique_ptr<std::thread> _eventThread;

	Client* _owner;

	volatile bool _isRunning;

	std::mutex _mutex;
};

