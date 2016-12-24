#include "stdafx.h"
#include "InputManager.h"
#include <iostream>
#include "Client.h"

InputManager::InputManager(Client* theOwner) : _text("")
{
	_owner = theOwner;
}


InputManager::~InputManager()
{
}

void InputManager::Execute(sf::RenderWindow& window)
{
	sf::Event event;

	// do until there is no more event to execute
	while (window.pollEvent(event))
	{
		// if we press a key on the keyboard
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode < 128)
			{
				// escape key
				if (event.key.code == ESCAPE_KEY)
				{
					fprintf(stderr, "Stopping application... \n");
					_owner->Stop();
				}
				// backscape key
				else if (event.key.code == BACKSPACE_KEY)
				{
					if(_text.size() > 0)
						_text = _text.substr(0, _text.size() - 1);
				}
				// enter key
				else if (event.key.code == ENTER_KEY)
				{
					_owner->Send(_text);
					_text = "";
				}
				else
				{
					_text += static_cast<char>(event.text.unicode);
				}
			}
		}
	}
}

std::string InputManager::GetText()
{
	return _text;
}
