#pragma once
#include <SFML/Graphics.hpp>
#include "LogicTicTacToe.h"

class GameRenderer {

private:
    sf::RenderWindow Window;
    sf::Vector2f CellSize;

    void DrawX(int positionX, int positionY);
    void DrawO(int positionX, int positionY);

public:
    GameRenderer(); //Constructeur
    sf::RenderWindow* GetWindow();
    sf::Vector2f GetCellSize();

    void InitializeWindow(const sf::Vector2f Bord); //initialise la Window
    void DrawBoard(const sf::Vector2f Bord); //désine le Tableau
    void DrawSymbol(const sf::Vector2f Bord, std::vector<std::vector<char>> BordSymbol); //désine les symbols
    
    void DisplayResult(const std::string& result);
    bool AskForRestart();
};