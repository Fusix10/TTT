#include <iostream>
#include "LogicTicTacToe.h"
#include "GameRender.h"

int main()
{
    LogicTicTacToe ticTacToeLogic;  // Instance de la logique du jeu
    GameRenderer gameRenderer;  // Instance du rendu du jeu

    // Initialisation de la fenêtre SFML avec la logique du jeu
    ticTacToeLogic.Starter();
    gameRenderer.InitializeWindow(ticTacToeLogic);

    gameRenderer.DrawBoard(ticTacToeLogic);
    while (true) {
        std::vector<std::vector<char>> Wait = ticTacToeLogic.GetBordSymbol();
        gameRenderer.HandleEvents(ticTacToeLogic);
        if (Wait != ticTacToeLogic.GetBordSymbol()) {
            gameRenderer.DrawBoard(ticTacToeLogic);
            gameRenderer.DrawSymbol(ticTacToeLogic);
        }
        if (ticTacToeLogic.CheckWin()) {
            // Afficher le résultat de la partie (gagné)
            gameRenderer.DisplayResult("Joueur " + std::to_string(ticTacToeLogic.GetActuelPlayer()) + " a gagné !");

            // Demander si le joueur veut recommencer
            if (gameRenderer.AskForRestart()) {
                ticTacToeLogic.ReStart();  // Recommencer la partie
            }
            else {
                break;  // Sortir de la boucle si le joueur ne veut pas recommencer
            }
        }
        else if (ticTacToeLogic.CheckNul()) {
            // Afficher le résultat de la partie (match nul)
            gameRenderer.DisplayResult("Match nul !");

            // Demander si le joueur veut recommencer
            if (gameRenderer.AskForRestart()) {
                ticTacToeLogic.ReStart();  // Recommencer la partie
            }
            else {
                break;  // Sortir de la boucle si le joueur ne veut pas recommencer
            }
        }

        // Mettre en pause pour éviter le rendu trop rapide
    }
    return 0;
}