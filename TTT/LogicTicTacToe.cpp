#include "LogicTicTacToe.h"

LogicTicTacToe::LogicTicTacToe() {
    ActuelPlayer = 1;//Joueur 1 de start 
    //GameEnded = false;//partie finie = false, donc la game est en cours
}

void LogicTicTacToe::Starter() {
    // Initialisation du plateau (par exemple, 3x3)
    Bord = {{' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}};
}

void LogicTicTacToe::MakeMove(int Player, int PosX, int PosY) {
    if (PosX >= 0 && PosX < Bord.size() && PosY >= 0 && PosY < Bord[0].size() && Bord[PosX][PosY] == ' ') { // Vérifie si la position est valide et non occupée

        if (Player == 1) {
            Bord[PosX][PosY] = 'x'; // 'x' pour le joueur 1
            ActuelPlayer = 2;
        }
        else {
            Bord[PosX][PosY] = 'o'; // 'o' pour le joueur 2
            ActuelPlayer = 1;
        }
    }
    else
    {
        ErrorMessage = "Position Invalide ou deja occuper, veuiller en choisir une autre";
    }
}

bool LogicTicTacToe::CheckWin() {
    for (int i = 0; i < Bord.size(); ++i) {
        // Vérification des colonnes
        if (Bord[i][0] != ' ' && Bord[i][0] == Bord[i][1] && Bord[i][1] == Bord[i][2]) {
            return true;
        }

        // Vérification des lignes
        if (Bord[0][i] != ' ' && Bord[0][i] == Bord[1][i] && Bord[1][i] == Bord[2][i]) {
            return true;
        }
    }

    // Vérification des diagonales
    if (Bord[0][0] != ' ' && Bord[0][0] == Bord[1][1] && Bord[1][1] == Bord[2][2]) {
        return true;
    }

    if (Bord[0][2] != ' ' && Bord[0][2] == Bord[1][1] && Bord[1][1] == Bord[2][0]) {
        return true;
    }

    return false;
}

bool LogicTicTacToe::CheckNul() {

    for (int i = 0; i < Bord.size(); i++) { //i pour les x
        for (int j = 0; j < Bord[i].size(); j++) { //j pour les y

            if (Bord[i][j] == ' ') { //je vérifie juste si il y a au moin 1 case vide si oui alors je retourne faux
                return false;
            }
        }
    }
    return true; //sinon c'est que tout les case sont remplie donc matche nul
}

void LogicTicTacToe::ReStart() {
    for (int i = 0; i < Bord.size(); i++) { //i pour les x
        for (int j = 0; j < Bord[i].size(); j++) { //j pour les y
            Bord[i][j] = ' '; // j'éfface le tableau
        }
    }

    ActuelPlayer = 1; // je redonne la main au joueur 1
    //GameEnded = false; // je remet l'état de la partie a false
}

int LogicTicTacToe::GetActuelPlayer() const {
    return ActuelPlayer;
}

std::string LogicTicTacToe::GetErrorMessage() const {
    return ErrorMessage;
}

sf::Vector2f LogicTicTacToe::GetBord() const {
    sf::Vector2f Recup;
    Recup.x = Bord.size();
    Recup.y = Bord[0].size();
    return Recup;
};

std::vector<std::vector<char>> LogicTicTacToe::GetBordSymbol() const {
    return Bord;
};