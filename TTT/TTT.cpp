#include <iostream>
#include "LogicTicTacToe.h"
#include "GameRender.h"


int main()
{
    LogicTicTacToe ticTacToeLogic;  // Instance de la logique du jeu
      // Instance du rendu du jeu
    GameRenderer gameRenderer;
    // Initialisation de la fen�tre SFML avec la logique du jeu
    ticTacToeLogic.Starter();
    gameRenderer.InitializeWindow(ticTacToeLogic);

    gameRenderer.DrawBoard(ticTacToeLogic);
    //Game(ticTacToeLogic, gameRenderer);
    while (true) {
        std::vector<std::vector<char>> Wait = ticTacToeLogic.GetBordSymbol();
        gameRenderer.HandleEvents(ticTacToeLogic);
        if (Wait != ticTacToeLogic.GetBordSymbol()) {
            gameRenderer.DrawBoard(ticTacToeLogic);
            gameRenderer.DrawSymbol(ticTacToeLogic);
        }
        if (ticTacToeLogic.CheckWin()) {
            // Afficher le r�sultat de la partie (gagn�)
            gameRenderer.DisplayResult("Joueur " + std::to_string(ticTacToeLogic.GetActuelPlayer()) + " a gagn� !");

            // Demander si le joueur veut recommencer
            if (gameRenderer.AskForRestart()) {
                ticTacToeLogic.ReStart();  // Recommencer la partie
                ticTacToeLogic.Starter();
                gameRenderer.InitializeWindow(ticTacToeLogic);

                gameRenderer.DrawBoard(ticTacToeLogic);
            }
            else {
                return 0;  // Sortir de la boucle si le joueur ne veut pas recommencer
            }
        }
        else if (ticTacToeLogic.CheckNul()) {
            // Afficher le r�sultat de la partie (match nul)
            gameRenderer.DisplayResult("Match nul !");

            // Demander si le joueur veut recommencer
            if (gameRenderer.AskForRestart()) {
                ticTacToeLogic.ReStart();  // Recommencer la partie
                ticTacToeLogic.Starter();
                gameRenderer.InitializeWindow(ticTacToeLogic);

                gameRenderer.DrawBoard(ticTacToeLogic);
            }
            else {
                return 0;  // Sortir de la boucle si le joueur ne veut pas recommencer
            }
        }

        // Mettre en pause pour �viter le rendu trop rapide
    }
    return 0;
}

int Game(LogicTicTacToe ticTacToeLogic, GameRenderer gameRenderer)
{
    return 0;
}