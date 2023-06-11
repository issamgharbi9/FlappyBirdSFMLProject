#include "Pipe.h"
#include "Globals.h"

Pipe::Pipe(int yPos)
{
    spriteDown.setTexture(textureDown);
    spriteUp.setTexture(textureUp);

    spriteDown.setScale(ScaleFactor, ScaleFactor);
    spriteUp.setScale(ScaleFactor, ScaleFactor);

    spriteUp.setPosition(WinWidth, yPos);
    spriteDown.setPosition(WinWidth, yPos - pipeDistance - spriteUp.getGlobalBounds().height);
}

void Pipe::update(sf::Time& dt)
{
    spriteDown.move( -moveSpeed * dt.asSeconds(), 0.f);
    spriteUp.move(-moveSpeed * dt.asSeconds(), 0.f);
}

void Pipe::loadtextures()
{
    textureDown.loadFromFile("C:/Users/HUAWEI MATE/OneDrive/Documents/FlappyBirdSFMLProject/assests/pipedown.png");
    textureUp.loadFromFile("C:/Users/HUAWEI MATE/OneDrive/Documents/FlappyBirdSFMLProject/assests/pipe.png");
}

float Pipe::getRightBound()
{
    return spriteDown.getGlobalBounds().left + spriteDown.getGlobalBounds().width;
}

 sf::Texture Pipe::textureDown, Pipe::textureUp;
 int Pipe::pipeDistance=180, Pipe::moveSpeed=400;
