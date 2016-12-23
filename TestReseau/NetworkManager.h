#pragma once

#include <thread>
#include <enet/enet.h>

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	void InitializeNetwork();

	void JoinThreads();

	void HandlesEvent();
	void HandlesInput();

private:
	ENetHost* _client;

	std::thread* _first;
};

