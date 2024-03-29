#include "Game.h"
#include "Globals.h"
#include "Bird.h"
#include "Pipe.h"
#include <sstream>

Game::Game(sf::RenderWindow& window) : win(window), isEnterPressed(false), runGame(true), startMonitoring(false),
    pipeCounter(71), pipeSpawnTime(70), score(0)
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

    font.loadFromFile("C:/Users/HUAWEI MATE/OneDrive/Documents/FlappyBirdSFMLProject/assests/arial.ttf");
    restartText.setFont(font);
    restartText.setCharacterSize(40);
    restartText.setFillColor(sf::Color::Black);
    restartText.setPosition(160, 650);
    restartText.setString("Restart Game !!");

    scoretext.setFont(font);
    scoretext.setCharacterSize(25);
    scoretext.setFillColor(sf::Color::Black);
    scoretext.setPosition(15,15);
    scoretext.setString("Score : 0");


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
        checkScore();
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
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left &&
                    !runGame)
            {
                if(restartText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                    restartGame();
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
    win.draw(scoretext);

    if(!runGame){
        win.draw(restartText);
    }
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

void Game::restartGame()
{
    bird.resetBirdPosition();
    bird.setShouldFly(false);
    runGame = true;
    isEnterPressed = false;
    pipeCounter = 71;
    pipes.clear();
    score = 0;
    scoretext.setString("Score : 0");
}

void Game::checkScore()
{
    if(pipes.size() > 0){
        if(!startMonitoring){
            if(bird.birdSprite.getGlobalBounds().left > pipes[0].spriteDown.getGlobalBounds().left &&
                    bird.getRightBound() < pipes[0].getRightBound())
            {
                startMonitoring = true;
            }
        }else
        {
            if(bird.birdSprite.getGlobalBounds().left > pipes[0].getRightBound())
            {
                score++;
                scoretext.setString("Score : " + toString(score) );
                startMonitoring = false;
            }
        }
    }
}

std::string Game::toString(int num)
{
    std::stringstream ss;
    ss << num;
    return ss.str();

}
