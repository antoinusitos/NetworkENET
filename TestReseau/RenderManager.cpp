#include "stdafx.h"
#include "RenderManager.h"

RenderManager::RenderManager() : _windowWidth(800), _windowHeight(600)
{

}


RenderManager::~RenderManager()
{
	delete _window;
	delete _topRectangle;
	delete _bottomRectangle;
}

void RenderManager::InitSFML()
{
	// create the windows and all the sfml stuff
	_window = new sf::RenderWindow(sf::VideoMode(_windowWidth, _windowHeight), "Client");

	_topRectangle = new sf::RectangleShape(sf::Vector2f(_windowWidth, _windowHeight  * 0.90));
	_topRectangle->setFillColor(sf::Color(0, 250, 0));
	_topRectangle->setPosition(sf::Vector2f(0, 0));
	_topRectangle->setOutlineThickness(-10);
	_topRectangle->setOutlineColor(sf::Color(0, 0, 0));

	_bottomRectangle = new sf::RectangleShape(sf::Vector2f( _windowWidth, _windowHeight  * 0.10));
	_bottomRectangle->setFillColor(sf::Color(150, 250, 50));
	_bottomRectangle->setPosition(sf::Vector2f(0, _windowHeight  * 0.90));
	_bottomRectangle->setOutlineThickness(-10);
	_bottomRectangle->setOutlineColor(sf::Color(0, 0, 0));
}

void RenderManager::Draw()
{
	PollEvents();

	_window->clear();
	_window->draw(*_topRectangle);
	_window->draw(*_bottomRectangle);
	_window->display();
}

bool RenderManager::IsWindowOpen()
{
	return _window->isOpen();
}

void RenderManager::PollEvents()
{
	sf::Event event;

	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window->close();
	}
}
