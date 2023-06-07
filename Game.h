#pragma once
#include <SFML/Graphics.hpp>
#include "Bird.h"
#include "bird.cpp"


class Game
{
public:
    Game(sf::RenderWindow& window);
    sf::RenderWindow& win;
    void startGameLoop();

private:
    sf::Texture backGroundTexture, groundTexture;
    sf::Sprite backGroundSprite, groundSprite1, groundSprite2;
    sf::Clock clock;
    Bird bird;
    bool isEnterPressed, runGame;
    const int moveSpeed=270;
    void draw();
    void moveGround(sf::Time&);
};
