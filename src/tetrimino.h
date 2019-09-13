#ifndef TETRIMINO_H
#define TETRIMINO_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>

/** Klasa  Tetrimino
 * Klasa predstavlja komad na ploči.
 *
 */
class Tetrimino{
public:
    // Tip komada. Imamo 7 različiti komasa (SIZE=7).
    enum Types {O=0,I,S,Z,L,J,T,SIZE};
    // Broj rotacija svakog komada.
    static const int N_ROTACIJA = 4;
    // Matrica koja sadrži svaki mogući komad je reda MAT_SIZExMAT_SIZE.
    static const int MAT_SIZE = 4;
    // Svi komadi i njihove rotacije su dane u ovoj tabeli.
    static const int mDijelovi[SIZE][N_ROTACIJA][MAT_SIZE][MAT_SIZE];
    // Boje pojedinih komada.
    static const sf::Color mColors[SIZE];

    // Tip komada.
    Types mType = O;
    // Trenutna rotacija komada.
    int mRotacija=0;
    // Trenutna pozicija komada.
    int mXposition=3, mYposition=-1;
    // Sat za mjerenje proteklog vremena
    sf::Clock mClock;

    void move(int x, int y){ mXposition += x; mYposition += y; }
    void rotate(){ mRotacija = (mRotacija+1) % N_ROTACIJA; }

    void newPiece(int i);
private:


};

#endif // TETRIMINO_H
