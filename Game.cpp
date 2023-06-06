#include "Game.h"
#include "Globals.h"

Game::Game(sf::RenderWindow& window) : win(window)
{
    backGroundTexture.loadFromFile("C:/Users/HUAWEI MATE/OneDrive/Documents/FlappyBirdSFMLProject/assests/background.png");
    backGroundSprite.setTexture(backGroundTexture);
    backGroundSprite.setScale(ScaleFactor, ScaleFactor);
    backGroundSprite.setPosition(0.f, -250.f);

    groundTexture.loadFromFile("C:/Users/HUAWEI MATE/OneDrive/Documents/FlappyBirdSFMLProject/assests/ground.png");
    groundSprite1.setTexture(groundTexture);
    groundSprite2.setTexture(groundTexture);

    groundSprite1.setScale(ScaleFactor, ScaleFactor);
    groundSprite2.setScale(ScaleFactor,ScaleFactor);

    groundSprite1.setPosition(0, 580);
    groundSprite2.setPosition(groundSprite1.getGlobalBounds().width,580);
}

void Game::startGameLoop()
{
    sf::Clock clock;
    //Game loop
    while(win.isOpen()){
        sf::Time dt = clock.restart();
        sf::Event event;
        //Event loop
        while(win.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                win.close();
            }
        }
        moveGround(dt);

        draw();
        //display the window "win"
        win.display();
    }
}

void Game::draw()
{
    win.draw(backGroundSprite);
    win.draw(groundSprite1);
    win.draw(groundSprite2);
}

void Game::moveGround(sf::Time& dt)
{
    //looping the ground
    groundSprite1.move(-moveSpeed * dt.asSeconds(), 0.f);
    groundSprite2.move(-moveSpeed * dt.asSeconds(), 0.f);

    //new position for ground 1
    if(groundSprite1.getGlobalBounds().left + groundSprite1.getGlobalBounds().width <0){
        groundSprite1.setPosition(groundSprite2.getGlobalBounds().left + groundSprite2.getGlobalBounds().width, 580);
    }
    //new position for ground 2
    if(groundSprite2.getGlobalBounds().left + groundSprite2.getGlobalBounds().width <0){
        groundSprite2.setPosition(groundSprite1.getGlobalBounds().left + groundSprite1.getGlobalBounds().width, 580);
    }

}
