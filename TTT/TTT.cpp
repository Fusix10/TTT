#include <iostream>
#include "LogicTicTacToe.h"
#include "GameRender.h"
#include "Client.h";
#include "InputManager.h";


int main()
{
    LogicTicTacToe ticTacToeLogic;  // Instance de la logique du jeu
      // Instance du rendu du jeu
    GameRenderer gameRenderer;

    InputManager ManagerInput;
    // Initialisation de la fenêtre SFML avec la logique du jeu
    ticTacToeLogic.Starter();
    gameRenderer.InitializeWindow(ticTacToeLogic.GetBord());

    gameRenderer.DrawBoard(ticTacToeLogic.GetBord());
    Client client;
    client.Send(32*3, 0, 1);
    //Game(ticTacToeLogic, gameRenderer);
    std::vector<std::vector<char>> RecupBord;
    while (true) {
        client.Update();
        int RecupPlayer = ticTacToeLogic.GetActuelPlayer();
        ManagerInput.HandleEvents(ticTacToeLogic.GetBord(), gameRenderer.GetWindow(), gameRenderer.GetCellSize(), &ticTacToeLogic);
        if(ticTacToeLogic.GetActuelPlayer() != RecupPlayer){
            gameRenderer.DrawBoard(ticTacToeLogic.GetBord());
            gameRenderer.DrawSymbol(ticTacToeLogic.GetBord(), ticTacToeLogic.GetBordSymbol());
        }

        if (ticTacToeLogic.CheckWin()) {
            // Afficher le résultat de la partie (gagné)
            gameRenderer.DisplayResult("Joueur " + std::to_string(ticTacToeLogic.GetActuelPlayer()) + " a gagné !");
                        // Demander si le joueur veut recommencer
            if (gameRenderer.AskForRestart()) {
                ticTacToeLogic.ReStart();  // Recommencer la partie
                ticTacToeLogic.Starter();
                gameRenderer.InitializeWindow(ticTacToeLogic.GetBord());

                gameRenderer.DrawBoard(ticTacToeLogic.GetBord());
            }
            else {
                return 0;  // Sortir de la boucle si le joueur ne veut pas recommencer
            }
        }
        else if (ticTacToeLogic.CheckNul()) {
            // Afficher le résultat de la partie (match nul)
            gameRenderer.DisplayResult("Match nul !");

            // Demander si le joueur veut recommencer
            if (gameRenderer.AskForRestart()) {
                ticTacToeLogic.ReStart();  // Recommencer la partie
                ticTacToeLogic.Starter();
                gameRenderer.InitializeWindow(ticTacToeLogic.GetBord());

                gameRenderer.DrawBoard(ticTacToeLogic.GetBord());
            }
            else {
                return 0;  // Sortir de la boucle si le joueur ne veut pas recommencer
            }
        }

        // Mettre en pause pour éviter le rendu trop rapide
    }
    return 0;
}
