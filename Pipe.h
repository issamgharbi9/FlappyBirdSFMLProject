#pragma once
#include <SFML/Graphics.hpp>


class Pipe
{
public:
    Pipe(int);
    sf::Sprite spriteUp, spriteDown;
    static void loadtextures();
    void update(sf::Time&);
    float getRightBound();

private:
    static sf::Texture textureUp, textureDown;
    static int pipeDistance, moveSpeed;
};
