#pragma once
#include <SFML/Graphics.hpp>
#include "Bird.h"
#include "bird.cpp"
#include <vector>
#include "Pipe.h"
#include <random>
#include "Pipe.cpp"

class Game
{
public:
    Game(sf::RenderWindow& window);
    sf::RenderWindow& win;
    void startGameLoop();

private:
    sf::Texture backGroundTexture, groundTexture;
    sf::Sprite backGroundSprite, groundSprite1, groundSprite2;
    Bird bird;
    bool isEnterPressed, runGame, startMonitoring;
    const int moveSpeed=270;
    void draw();
    void moveGround(sf::Time&);
    void doProcessing(sf::Time& dt);
    void checkCollisions();
    void restartGame();
    void checkScore();
    std::string toString(int);
    int pipeCounter, pipeSpawnTime, score;
    std::vector<Pipe> pipes;
    std::random_device rd;
    std::uniform_int_distribution<int> dist{250, 550};
    sf::Font font;
    sf::Text restartText, scoretext;

};
