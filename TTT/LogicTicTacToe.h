#pragma once

#include <vector>
#include <string>
#include <SFML/System/Vector2.hpp>

class LogicTicTacToe
{
public:
    LogicTicTacToe();  // Constructeur

    void Starter();  // Initialise le jeu
    void MakeMove(int Player, int PosX, int PosY);  // Enregistre le mouvement d'un joueur
    bool CheckWin();  // Vérifie s'il y a un gagnant
    bool CheckNul();  // Vérifie s'il y a match nul
    void ReStart();  // Recommence la partie

    int GetActuelPlayer() const;
    std::string GetErrorMessage() const;
    sf::Vector2f GetBord() const;
    std::vector<std::vector<char>> GetBordSymbol() const;

private:
    std::string ErrorMessage;
    std::vector<std::vector<char>> Bord;  // Représentation du plateau de jeu
    int ActuelPlayer;  // Indique quel joueur doit jouer (1 ou 2)
    //bool GameEnded;  // Indique si la partie est terminée
};
