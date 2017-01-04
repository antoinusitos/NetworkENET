#include "stdafx.h"
#include "RenderManager.h"
#include <iostream>

RenderManager::RenderManager() : _windowWidth(800.f), _windowHeight(600.f)
{
	_conversation = new std::vector<std::string>();
}

RenderManager::~RenderManager()
{
	//delete _window;
	delete _topRectangle;
	delete _bottomRectangle;
}

void RenderManager::InitSFML()
{
	// create the windows and all the sfml stuff
	_window.create(sf::VideoMode(_windowWidth, _windowHeight), "Client");

	_topRectangle = new sf::RectangleShape(sf::Vector2f(_windowWidth, _windowHeight  * 0.90f));
	_topRectangle->setFillColor(sf::Color(0, 250, 0));
	_topRectangle->setPosition(sf::Vector2f(0, 0));
	_topRectangle->setOutlineThickness(-10);
	_topRectangle->setOutlineColor(sf::Color(0, 0, 0));

	_bottomRectangle = new sf::RectangleShape(sf::Vector2f( _windowWidth, _windowHeight  * 0.10f));
	_bottomRectangle->setFillColor(sf::Color(150, 250, 50));
	_bottomRectangle->setPosition(sf::Vector2f(0, _windowHeight  * 0.90f));
	_bottomRectangle->setOutlineThickness(-10);
	_bottomRectangle->setOutlineColor(sf::Color(0, 0, 0));

	if (!_font.loadFromFile("Resources/Font/arial.ttf"))
	{
		std::cout << "Missing the font at address : Resources/Font/arial.ttf" << std::endl;
	}
	_text.setFont(_font);
	_text.setCharacterSize(24);
	_text.setFillColor(sf::Color::Red);
	_text.setPosition(sf::Vector2f(10, _windowHeight  * 0.93f));
}

void RenderManager::Draw()
{
	PollEvents();

	_window.clear();
	_window.draw(*_topRectangle);
	RenderConversation();
	_window.draw(*_bottomRectangle);
	_window.draw(_text);
	_window.display();

}

bool RenderManager::IsWindowOpen()
{
	return _window.isOpen();
}

sf::RenderWindow& RenderManager::GetWindow()
{
	return _window;
}

void RenderManager::UpdateInputText(std::string text)
{
	_text.setString(text);
}

void RenderManager::ReceiveText(std::string text)
{
	_conversation->push_back(text);
}

void RenderManager::PollEvents()
{
	sf::Event event;

	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window.close();
	}
}

void RenderManager::RenderConversation()
{
	sf::Text aText;
	aText.setFont(_font);
	aText.setCharacterSize(24);
	aText.setFillColor(sf::Color::Red);

	for (int i = 0; i < _conversation->size(); i++)
	{
		aText.setString(_conversation->at(i));
		aText.setPosition(sf::Vector2f(10, 10 + i * 20));
		_window.draw(aText);
	}
}
