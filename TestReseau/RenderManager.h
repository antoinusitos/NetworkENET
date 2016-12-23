#pragma once

#include <SFML/Graphics.hpp>

class RenderManager
{
public:
	RenderManager();
	~RenderManager();

	void InitSFML();
	void Draw();

	bool IsWindowOpen();

private:
	sf::RenderWindow* _window;
	sf::RectangleShape* _topRectangle;
	sf::RectangleShape* _bottomRectangle;

	void PollEvents();

	int _windowWidth;
	int _windowHeight;
};

