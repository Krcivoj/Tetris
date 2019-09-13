#pragma once
#include <SFML/Graphics.hpp>

/** Klasa Score
 * Ona se brine o prikazu rezultata
 *
 */

class Score : public sf::Drawable, public sf::Transformable{
public:
    Score();
    void addNoLinesCompleted(int n);
    void update();
    int  getScore() const { return mScore; }
    void clearState ();
private:
    sf::Font mFont;
    sf::Text mScoreText;
    int mTotalLinesCompleted = 0;
    int mScore = 0;

    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};
