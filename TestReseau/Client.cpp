#include "stdafx.h"
#include "Client.h"
#include <iostream>
#include "NetworkManager.h"
#include "InputManager.h"
#include "RenderManager.h"

Client::Client() : _clientName("UNKNOWN")
{
	InitName();

	_inputManager = new InputManager(this);
	_networkManager = new NetworkManager(this);
	_renderManager = new RenderManager();

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

		// Get Input from keyboard
		_inputManager->Execute(_renderManager->GetWindow());
		// Get the text in input
		_renderManager->UpdateInputText(_inputManager->GetText());
		// Draw the window and the text
		_renderManager->Draw();

	}
}

void Client::Stop()
{
	_isRunning = false;
}

void Client::Send(std::string text)
{
	_networkManager->SendText(text);
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