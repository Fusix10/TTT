#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "LogicTicTacToe.h"

class InputManager
{
public:
	InputManager();
	sf::Vector2f GetMouse();
	void HandleEvents(const sf::Vector2f Bord, sf::RenderWindow* Window, sf::Vector2f CellSize, LogicTicTacToe *MakeMouve);
private:
	sf::Vector2f Mouse;
};

