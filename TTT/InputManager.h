#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
class InputManager
{
public:

private:
	void HandleEvents(const sf::Vector2f Bord, sf::RenderWindow *Window, sf::Vector2f CellSize);
	sf::Vector2f Mouse;
};

