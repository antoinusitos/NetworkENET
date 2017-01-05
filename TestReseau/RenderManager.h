#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class RenderManager
{
public:
	RenderManager();
	~RenderManager();

	void Init();
	void Draw();

	bool IsWindowOpen();

	sf::RenderWindow& GetWindow();
	void UpdateInputText(std::string text);

	void ReceiveText(std::string text);

private:
	sf::RenderWindow _window;
	sf::RectangleShape* _topRectangle;
	sf::RectangleShape* _bottomRectangle;

	void PollEvents();

	float _windowWidth;
	float _windowHeight;

	sf::Font _font;
	sf::Text _text;

	std::vector<std::string>* _conversation;
	void RenderConversation();
};

