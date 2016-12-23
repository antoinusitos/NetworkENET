#pragma once

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

	InputManager* GetInputManager();
	NetworkManager* GetNetworkManager();
	RenderManager* GetRenderManager();

	void Run();

private:
	char* _clientName;

	NetworkManager* _networkManager;
	InputManager* _inputManager;
	RenderManager* _renderManager;

	bool _isRunning;

	void InitName();
};

