#include "GameRender.h"
#include <iostream>


GameRenderer::GameRenderer() {
    // Initialise d'autres éléments si nécessaire
    CellSize.x = 0;
    CellSize.y = 0;
}

void GameRenderer::InitializeWindow(const LogicTicTacToe& ticTacToeLogic) {
    Window.create(sf::VideoMode(1920, 1080), "Tic Tac Toe SFML"); //taille + nom de la Window
    CellSize.x = static_cast<float>(Window.getSize().x) / static_cast<float>(ticTacToeLogic.GetBord().x);
    CellSize.y = static_cast<float>(Window.getSize().y) / static_cast<float>(ticTacToeLogic.GetBord().y);
}

void GameRenderer::DrawBoard(const LogicTicTacToe& ticTacToeLogic) {
    Window.clear();  // Efface le contenu précédent

    // Dessine les lignes verticales
    for (int i = 1; i < ticTacToeLogic.GetBord().x; ++i) {
        sf::VertexArray Line(sf::Lines, 2);
        Line[0].position = sf::Vector2f(i * CellSize.x, 0);
        Line[1].position = sf::Vector2f(i * CellSize.x, static_cast<float>(Window.getSize().y));
        Window.draw(Line);
    }


    // Dessine les lignes horizontales
    for (int j = 1; j < ticTacToeLogic.GetBord().y; ++j) {
        sf::VertexArray Line(sf::Lines, 2);
        Line[0].position = sf::Vector2f(0, j * CellSize.y);
        Line[1].position = sf::Vector2f(static_cast<float>(Window.getSize().x), j * CellSize.y);
        Window.draw(Line);
    }

    Window.display();
}

void GameRenderer::DrawSymbol(const LogicTicTacToe& ticTacToeLogic) {

    for (int i = 0; i < ticTacToeLogic.GetBord().x; ++i) {
        for (int j = 0; j < ticTacToeLogic.GetBord().y; ++j) {
            if (ticTacToeLogic.GetBordSymbol()[i][j] == 'x') {
                DrawX(i, j);
            }
            else if (ticTacToeLogic.GetBordSymbol()[i][j] == 'o') {
                DrawO(i, j);
            }
        }
    }

    Window.display();
}

void GameRenderer::DrawX(int positionX, int positionY) {
    // Dessine un X à la position spécifiée
    sf::VertexArray cross(sf::Lines, 4);
    cross[0].position = sf::Vector2f(positionX * CellSize.x, positionY * CellSize.y);
    cross[1].position = sf::Vector2f((positionX + 1) * CellSize.x, (positionY + 1) * CellSize.y);
    cross[2].position = sf::Vector2f((positionX + 1) * CellSize.x, positionY * CellSize.y);
    cross[3].position = sf::Vector2f(positionX * CellSize.x, (positionY + 1) * CellSize.y);

    cross[0].color = sf::Color::Red;
    cross[1].color = sf::Color::Red;
    cross[2].color = sf::Color::Red;
    cross[3].color = sf::Color::Red;

    Window.draw(cross);
}

void GameRenderer::DrawO(int positionX, int positionY) {
    // Dessine un O à la position spécifiée
    sf::CircleShape circle(CellSize.x / 4);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition((positionX + 0.5) * CellSize.x, (positionY + 0.5) * CellSize.y);
    circle.setFillColor(sf::Color::Blue);

    Window.draw(circle);
}

void GameRenderer::HandleEvents(LogicTicTacToe& ticTacToeLogic) {
    sf::Event event;
    while (Window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            Window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // Convertir les coordonnées de la souris en indices de tableau
                int mouseX = event.mouseButton.x / CellSize.x;
                int mouseY = event.mouseButton.y / CellSize.y;

                // S'assurer que les indices sont dans les limites du tableau
                if (mouseX >= 0 && mouseX < ticTacToeLogic.GetBord().x && mouseY >= 0 && mouseY < ticTacToeLogic.GetBord().y) {
                    // Effectuer le mouvement
                    ticTacToeLogic.MakeMove(ticTacToeLogic.GetActuelPlayer(), mouseX, mouseY);
                }
            }
        }
    }
}

void GameRenderer::DisplayResult(const std::string& result) {
    // Crée un texte avec la police par défaut de SFML
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        return;
    }

    sf::Text resultText(result, font, 30);
    resultText.setFillColor(sf::Color::White);

    // Centrer le texte sur la fenêtre
    sf::FloatRect textRect = resultText.getLocalBounds();
    resultText.setPosition(Window.getSize().x / 2 - textRect.width / 2, Window.getSize().y / 2 - textRect.height / 2);

    // Dessiner le texte
    Window.draw(resultText);

    // Afficher le contenu
    Window.display();

    // Attente de 3 secondes
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < 3) {
        // Boucle vide
    }

    // Effacer le contenu après l'attente
    Window.clear();
    Window.display();
}

bool GameRenderer::AskForRestart() {
    // Efface le contenu précédent
    Window.clear();

    // Crée un texte avec la police par défaut de SFML pour demander si le joueur veut recommencer
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        return false;  // En cas d'erreur de chargement de la police, retourne false
    }

    sf::Text restartText("Voulez-vous recommencer ? (O/N)", font, 30);
    restartText.setFillColor(sf::Color::White);

    // Centrer le texte sur la fenêtre
    sf::FloatRect textRect = restartText.getLocalBounds();
    restartText.setPosition(Window.getSize().x / 2 - textRect.width / 2, Window.getSize().y / 2 - textRect.height / 2);

    // Dessiner le texte
    Window.draw(restartText);

    // Afficher le contenu
    Window.display();

    // Attente de la réponse de l'utilisateur
    sf::Event event;
    int RePlay = 0;
    while (RePlay == 0) {
        Window.pollEvent(event);
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::O) {
                RePlay = 1;
            }
            else if (event.key.code == sf::Keyboard::N) {
                RePlay = 2;
            }
        }
    }
    if (RePlay == 1) {
        return true;
    }
    else if (RePlay == 2) {
        return false;
    }
}