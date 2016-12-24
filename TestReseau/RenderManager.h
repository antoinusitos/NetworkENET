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

	sf::RenderWindow& GetWindow();
	void UpdateInputText(std::string text);

private:
	sf::RenderWindow _window;
	sf::RectangleShape* _topRectangle;
	sf::RectangleShape* _bottomRectangle;

	void PollEvents();

	float _windowWidth;
	float _windowHeight;

	sf::Font _font;
	sf::Text _text;
};

