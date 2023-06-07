#pragma once
#include <SFML/Graphics.hpp>

class Bird
{
private:
    sf::Texture textures[2];
    const int gravity=10;
    const int flapSpeed=250;
    float velocityY;
    int animCounter,textureSwitch;
    float shouldFly;
public:
    Bird();
    sf::Sprite birdSprite;
    void setShouldFly(bool);
    void flapBird(sf::Time&);
    void resetBirdPosition();
    void update(sf::Time&);
    float getRightBound();
};
