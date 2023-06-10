#include "Game.h"
#include "Globals.h"
#include "Bird.h"
#include "Pipe.h"

Game::Game(sf::RenderWindow& window) : win(window), isEnterPressed(false), runGame(true),
    pipeCounter(71), pipeSpawnTime(70)
{
    win.setFramerateLimit(60);

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

    Pipe::loadtextures();
}

void Game::doProcessing(sf::Time& dt)
{
    if(isEnterPressed){
        moveGround(dt);
        if(pipeCounter > pipeSpawnTime){
            pipes.push_back(Pipe(dist(rd)));
            pipeCounter = 0;
        }
        pipeCounter++;
        for(int i=0 ; i<pipes.size() ; i++){
            pipes[i].update(dt);
            if(pipes[i].getRightBound() < 0){
                pipes.erase(pipes.begin() + i);
            }
        }
        checkCollisions();
    }
    bird.update(dt);
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
            if(event.type == sf::Event::KeyPressed && runGame){
                if(event.key.code == sf::Keyboard::Enter && !isEnterPressed){
                    isEnterPressed = true;
                    bird.setShouldFly(true); // to start the game
                }
                if(event.key.code == sf::Keyboard::Space && isEnterPressed){
                    bird.flapBird(dt); //to make the bird jump
                }
            }
        }

        doProcessing(dt);
        draw();
        //display the window "win"
        win.display();
    }
}

void Game::checkCollisions()
{
    if(pipes.size() > 0){
        if(pipes[0].spriteDown.getGlobalBounds().intersects(bird.birdSprite.getGlobalBounds()) ||
                pipes[0].spriteUp.getGlobalBounds().intersects(bird.birdSprite.getGlobalBounds()) ||
                bird.birdSprite.getGlobalBounds().top >= 542){
            isEnterPressed = false;
            runGame = false;
        }
    }
}

void Game::draw()
{
    win.draw(backGroundSprite);
    for(Pipe& pipe : pipes){
        win.draw(pipe.spriteDown);
        win.draw((pipe.spriteUp));
    }
    win.draw(groundSprite1);
    win.draw(groundSprite2);
    win.draw(bird.birdSprite);
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
