#include "playstate.h"
#include "game.h"


/** Implementacija klase PlayState
 *
 */


PlayState::PlayState(Game *pGame): GameState (pGame)
{

}

void PlayState::start()
{
    mBoard.clearState();
    mBoard.setSpeed(mpGame->mGameSpeed);
    mScore.clearState();
}

void PlayState::handleEvents(sf::Event event)
{
    if(event.type==sf::Event::KeyPressed){
        switch (event.key.code) {
        case sf::Keyboard::Left:
            mLeftPress=true;
            break;
        case sf::Keyboard::Right:
            mRightPress=true;
            break;
        case sf::Keyboard::Up:
            mUpPress=true;
            break;
        case sf::Keyboard::Space:
            mSpacePress=true;
            break;
        default: ;
        }
    }
}

void PlayState::update()
{
    if(mBoard.isBottom() && !mBoard.isGameOver())
        {
            mScore.addNoLinesCompleted(mBoard.getNoLinesCompleted());
            mBoard.spawnPiece();
        }
        if(!mBoard.isGameOver())mBoard.update(mLeftPress,mRightPress,mUpPress,mSpacePress);
        mLeftPress = false;
        mRightPress = false;
        mUpPress = false;
        mSpacePress = false;
        mScore.update();
        if(mBoard.isGameOver()){
            mpGame->mGameScore=mScore.getScore();
            mpGame->setState(GameState::State::Speed);
        }
}

void PlayState::render()
{
    mpGame->getWindow()->draw(mBoard);
    mpGame->getWindow()->draw(mScore);
}
