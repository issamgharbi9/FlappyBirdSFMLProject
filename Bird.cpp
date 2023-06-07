#include "Bird.h"
#include "Globals.h"

Bird::Bird() :
    gravity(10),
    flapSpeed(250),
    animCounter(0),
    textureSwitch(1),
    shouldFly(false)
{
    textures[0].loadFromFile("C:/Users/HUAWEI MATE/OneDrive/Documents/FlappyBirdSFMLProject/assests/birddown.png");
    textures[1].loadFromFile("C:/Users/HUAWEI MATE/OneDrive/Documents/FlappyBirdSFMLProject/assests/birdup.png");

    birdSprite.setTexture(textures[0]);
    birdSprite.setScale(ScaleFactor, ScaleFactor);
    resetBirdPosition();
}

void Bird::update(sf::Time& dt)
{
    if(birdSprite.getGlobalBounds().top < 550 && shouldFly){
        if(animCounter == 5){
            birdSprite.setTexture(textures[textureSwitch]);
            if(textureSwitch){
                textureSwitch=0;
            }else{
                textureSwitch=1;
            }
            animCounter=0;
        }
        animCounter++;

        velocityY += gravity * dt.asSeconds();
        birdSprite.move(0, velocityY);

        if(birdSprite.getGlobalBounds().top <0){
            birdSprite.setPosition(100, 0);
        }
    }
}

void Bird::flapBird(sf::Time& dt)
{
    velocityY = -flapSpeed * dt.asSeconds();
}

float Bird::getRightBound()
{
    return birdSprite.getGlobalBounds().left + birdSprite.getGlobalBounds().width;
}

void Bird::resetBirdPosition()
{
    birdSprite.setPosition(100, 50);
    velocityY = 0;
}

void Bird::setShouldFly(bool shouldFly)
{
    this->shouldFly = shouldFly;
}




