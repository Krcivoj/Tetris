#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
class Game;

/** Klasa GameState
 * Klasa WelcomeState
 * Klasa SpeedState
 *
 */

//GameState je virtualna klasa. Iz nje se izvode sva stanja igre.
class GameState
{
public:
    GameState(Game * pGame) : mpGame(pGame){}
    virtual ~GameState() {}
    // Sva moguća stanja igre.
        enum State{
            Welcome,
            Playing,
            Speed,
            SIZE
        };
    // Metode koje moraju osigurati sva stanja igre.
    virtual void handleEvents(sf::Event event) = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    // Restartanje igre. To će preraditi samo PlayState.
    virtual void start() {}

protected:
        Game * const mpGame;
};

//WelcomState predstavnja početni zaslon igre.
class WelcomeState : public GameState{
public:
    WelcomeState(Game * pGame);
    virtual void handleEvents(sf::Event event) override;
    virtual void update() override;
    virtual void render() override;
private:
    sf::Text mText1;
    sf::Text mText2;
    sf::Font mFont;

    bool mAnyPress=false;
};

//SpeedState je stanje između dvije igre.
class SpeedState : public GameState{
public:
    SpeedState(Game * pGame);
    virtual void handleEvents(sf::Event event) override;
    virtual void update() override;
    virtual void render() override;
private:
    sf::Text mText0;
    sf::Text mText1;
    sf::Text mText2;
    sf::Text mText3;
    sf::Font mFont;

    bool mUpPress=false;
    bool mDownPress=false;
    bool mEnterPress=false;

};

#endif // GAMESTATE_H
