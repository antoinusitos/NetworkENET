#pragma once

#include <SFML/Graphics.hpp>

#define ESCAPE_KEY 27
#define ENTER_KEY 13
#define BACKSPACE_KEY 8

class Client;

class InputManager
{
public:
	InputManager(Client* theOwner);
	~InputManager();

	void Execute(sf::RenderWindow& window);

	std::string GetText();

private:
	std::string _text;
	Client* _owner;
};

