#include "game.h"
#include "playstate.h"

#include <iostream>

/** Implementacija klase Game
 *
 */

Game::Game() : mWindow(sf::VideoMode(500,600), "Tetris"), mGameSpeed(3.0f),
               mGameScore(0)
{
    mAllStates[0] = new WelcomeState(this);
    mpGameState = mAllStates[0];
    mAllStates[1] = new PlayState(this);
    mAllStates[2] = new SpeedState(this);
}

Game::~Game()
{
    for(std::size_t i=0; i<GameState::State::SIZE; ++i)
        delete mAllStates[i];
}

void Game::run(){
    while(mWindow.isOpen()){
        processEvents();
        update();
        render();
    }
}

void Game::setState(GameState::State st)
{
    mpGameState = mAllStates[st];
    mpGameState->start();
}

sf::RenderWindow * Game::getWindow()
{
    return &mWindow;
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            mWindow.close();
        else if(event.type ==sf::Event::Resized){
            // Spriječi deformaciju objekata prilikom promjene veličine prozora
            sf::FloatRect viewRect(0, 0, event.size.width, event.size.height);
            mWindow.setView(sf::View(viewRect));
        }
        else {
            mpGameState->handleEvents(event);
		}
    }
}

void Game::update()
{
    mpGameState->update();
}

void Game::render()
{
     mWindow.clear();
     mpGameState->render();
     mWindow.display();
}
