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

    void InitializeWindow(const LogicTicTacToe& ticTacToeLogic); //initialise la Window
    void DrawBoard(const LogicTicTacToe& ticTacToeLogic); //d�sine le Tableau
    void DrawSymbol(const LogicTicTacToe& ticTacToeLogic); //d�sine les symbols
    void HandleEvents(LogicTicTacToe& ticTacToeLogic);
    void DisplayResult(const std::string& result);
    bool AskForRestart();
};