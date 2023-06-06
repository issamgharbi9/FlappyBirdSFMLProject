#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Game.h"
#include "Game.cpp"

using namespace std;

int main()
{
    sf::RenderWindow win(sf::VideoMode(WinWidth, WinHeight), "Flappy bird PUT lab Project");
    Game game(win);
    game.startGameLoop();

    return 0;
}



