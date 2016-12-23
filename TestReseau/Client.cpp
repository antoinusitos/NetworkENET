#include "stdafx.h"
#include "Client.h"
#include <iostream>
#include "NetworkManager.h"
#include "InputManager.h"
#include "RenderManager.h"

Client::Client() : _clientName("UNKNOWN")
{
	InitName();

	_inputManager = new InputManager();
	_networkManager = new NetworkManager;
	_renderManager = new RenderManager;

}

Client::~Client()
{
	if(_inputManager)
		delete _inputManager;
	if(_networkManager)
		delete _networkManager;
}

void Client::SetClientName(char* theName)
{
	_clientName = theName;
}

char* Client::GetClientName()
{
	return _clientName;
}

InputManager* Client::GetInputManager()
{
	return _inputManager;
}

NetworkManager* Client::GetNetworkManager()
{
	return _networkManager;
}

RenderManager* Client::GetRenderManager()
{
	return _renderManager;
}

void Client::Run()
{
	// galeplay loop
	_isRunning = true;

	_renderManager->InitSFML();

	_networkManager->InitializeNetwork();
	_networkManager->JoinThreads();

	while (_isRunning && _renderManager->IsWindowOpen())
	{
		// do stuff here
		_renderManager->Draw();

	}
}

void Client::InitName()
{
	fprintf(stderr, "Enter Your Name : \n");

	std::string name;
	std::getline(std::cin, name);
	char* cstr = new char[name.length() + 1];
	strcpy_s(cstr, strlen(cstr) + 1, name.c_str());

	_clientName = cstr;

	fprintf(stderr, "connecting... \n");
}

