#include "score.h"
#include <cstdlib>
#include <iostream>

/** Implementacija klase Score
 *
 */

Score::Score()
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf"))
        {
            std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf u Score!" << std::endl;
            std::exit(1);
        }

       mScoreText.setFont(mFont);
       auto s = std::to_string(mScore);
       mScoreText.setString("Score: "+s);
       mScoreText.setPosition(320,40);
       mScoreText.setStyle(sf::Text::Bold);
       mScoreText.setCharacterSize(30);
}

void Score::addNoLinesCompleted(int n)
{
    mTotalLinesCompleted+=n;
}

void Score::update()
{
    mScore=mTotalLinesCompleted*10;
    auto s = std::to_string(mScore);
    mScoreText.setString("Score: "+s);
}

void Score::clearState()
{
    mTotalLinesCompleted=0;
}

void Score::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *=getTransform();
    target.draw(mScoreText, states);
}
