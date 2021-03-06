#pragma once

#include <string>

class NetworkManager;
class InputManager;
class RenderManager;

class Client
{
public:
	Client();
	~Client();

	void SetClientName(char* theName);
	char* GetClientName();

	InputManager* GetInputManager() const;
	NetworkManager* GetNetworkManager() const;
	RenderManager* GetRenderManager() const;
	bool GetIsRunning() const;

	void Run();

	void Stop();

	void Send(std::string text);

private:
	char* _clientName;

	NetworkManager* _networkManager;
	InputManager* _inputManager;
	RenderManager* _renderManager;

	bool _isRunning;

	void InitName();
};

