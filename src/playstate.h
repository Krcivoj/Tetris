#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <SFML/Window/Event.hpp>

#include "gamestate.h"
#include "board.h"
#include "score.h"

/** Klasa PlayState
 * Ona predstavnja igrače stanje.
 *
 */

class PlayState : public GameState
{
public:
    PlayState(Game * pGame);
    void  start() override;
private:
    Board mBoard;
    Score mScore;

    virtual void handleEvents(sf::Event event) override;
    virtual void update() override;
    virtual void render() override;

    bool mLeftPress=false;
    bool mRightPress=false;
    bool mUpPress=false;
    bool mSpacePress=false;
};

#endif // PLAY_STATE_H
