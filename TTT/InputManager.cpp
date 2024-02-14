#include "InputManager.h"

InputManager::InputManager() {

};

void InputManager::HandleEvents(const sf::Vector2f Bord, sf::RenderWindow* Window, sf::Vector2f CellSize, LogicTicTacToe *MakeMouve) {
    sf::Event event;
    while (Window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            Window->close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // Convertir les coordonnées de la souris en indices de tableau
                Mouse.x = event.mouseButton.x / CellSize.x;
                Mouse.y = event.mouseButton.y / CellSize.y;

                // S'assurer que les indices sont dans les limites du 
                MakeMouve->MakeMove(MakeMouve->GetActuelPlayer(), Mouse.x, Mouse.y);
            }
        }
    }
}

sf::Vector2f InputManager::GetMouse(){
    return Mouse;
};