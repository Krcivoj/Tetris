#include "gamestate.h"
#include "game.h"
#include <cstdlib>
#include <iostream>

/** Implementacija GameState, WelcomeState, SpeedState
 *
 */

//Implementacija WelcomeState

WelcomeState::WelcomeState(Game *pGame): GameState (pGame)
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf"))
        {
            std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf u WelcomeState!" << std::endl;
            std::exit(1);
        }
    mText1.setFont(mFont);
    mText1.setStyle(sf::Text::Bold);
    mText1.setCharacterSize(50);
    mText2.setFont(mFont);
    mText2.setCharacterSize(25);

    mText1.setPosition(120,200);
    mText2.setPosition(130,260);

    mText1.setString("Tetris by Krci");
    mText2.setString("Press any key to continue.");
}

void WelcomeState::handleEvents(sf::Event event)
{
    if(event.type==sf::Event::KeyPressed)
        mAnyPress=true;
}

void WelcomeState::update()
{
    if(mAnyPress)mpGame->setState(GameState::State::Playing);
    mAnyPress=false;
}

void WelcomeState::render()
{
    mpGame->getWindow()->draw(mText1);
    mpGame->getWindow()->draw(mText2);
}

//Implementacija SpeedState

SpeedState::SpeedState(Game *pGame): GameState (pGame)
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf"))
        {
            std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf u SpeedState!" << std::endl;
            std::exit(1);
        }
    mText0.setFont(mFont);
    mText1.setFont(mFont);
    mText2.setFont(mFont);
    mText3.setFont(mFont);

    mText0.setStyle(sf::Text::Bold);
    mText1.setStyle(sf::Text::Bold);
    //mText2.setStyle(sf::Text::Bold);
    //mText3.setStyle(sf::Text::Bold);

    mText0.setCharacterSize(30);
    mText1.setCharacterSize(30);
    mText2.setCharacterSize(25);
    mText3.setCharacterSize(25);

    mText0.setPosition(200,190);
    mText1.setPosition(120,220);
    mText2.setPosition(50,270);
    mText3.setPosition(170,300);

    mText2.setString("Use keys Up and Down to change the speed.");
    mText3.setString("Enter to continue.");
}

void SpeedState::handleEvents(sf::Event event)
{
    if(event.type==sf::Event::KeyPressed){
        switch (event.key.code) {
        case sf::Keyboard::Up:
            mUpPress=true;
            break;
        case sf::Keyboard::Down:
            mDownPress=true;
            break;
        case sf::Keyboard::Return:
            mEnterPress=true;
            break;
        default:;
        }
    }
}

void SpeedState::update()
{
    if(mUpPress)
        mpGame->mGameSpeed+=0.5f;
    if(mDownPress && mpGame->mGameSpeed > 0.5f)
        mpGame->mGameSpeed-=0.5f;
    if(mEnterPress)
        mpGame->setState(GameState::State::Playing);
    mUpPress=false;
    mDownPress=false;
    mEnterPress=false;

    auto score = std::to_string(mpGame->mGameScore);
    mText0.setString("Score= "+ score);
    auto speed = std::to_string(mpGame->mGameSpeed);
    mText1.setString("Current speed= "+speed);
}

void SpeedState::render()
{
    mpGame->getWindow()->draw(mText0);
    mpGame->getWindow()->draw(mText1);
    mpGame->getWindow()->draw(mText2);
    mpGame->getWindow()->draw(mText3);
}
