#include "board.h"

/** Implementacija klase Board
 *
*/
Board::Board() :mGrid(sf::Quads), Grid(sf::Lines)
{
    mGrid.resize(200*4);
    for(std::size_t i=0; i<20; ++i)
        for(std::size_t j=0; j<10; ++j)
        {
            mGrid[4*(10*i+j)].position = sf::Vector2f(50+j*20,50+i*20 );
            mGrid[4*(10*i+j)+1].position = sf::Vector2f(50+(j+1)*20,50 + i*20 );
            mGrid[4*(10*i+j)+2].position = sf::Vector2f(50+(j+1)*20, 50+(i+1)*20);
            mGrid[4*(10*i+j)+3].position = sf::Vector2f(50+j*20, 50+(i+1)*20);
         }


    for(int i=0; i<mRows; i++){
       for(int j=0; j<mCols; j++){
           mGridContent[i][j]= EMPTY;
       }
    }

    Grid.resize(32*2);
        for(std::size_t i=0; i<21; ++i)
        {
            Grid[2*i].position=sf::Vector2f(50, 50+i*20);
            Grid[2*i+1].position=sf::Vector2f(250, 50+i*20);
        }
        for(std::size_t i=0; i<11; ++i)
        {
            Grid[2*(i+21)].position=sf::Vector2f(50+i*20, 50);
            Grid[2*(i+21)+1].position=sf::Vector2f(50+i*20, 450);
    }


}

Board::~Board()
{

}

void Board::update(bool LeftPress, bool RightPress, bool UpPress, bool SpacePress)
{
    if(LeftPress)
        movePiece(-1, 0);
    if(RightPress)
        movePiece(1, 0);
    if(UpPress)
        rotatePiece();
    if(SpacePress)
        while(movePiece(0,1));

    if(mPiece.mClock.getElapsedTime().asSeconds()>mDt){
        if(!movePiece(0,1)){
            mBottom=true;
            clearNoLinesCompleted();
            clearLines();
        }
        mPiece.mClock.restart();
    }

    color();
}

void Board::spawnPiece()
{
    std::uniform_int_distribution<> distribution(0, 6);
    mPiece.newPiece(mUniformDist(mRNE));
    mBottom=false;

    if(checkSpace())placePiece();
    else mGameOver=true;
}

void Board::clearState()
{
    for(int i=0; i<mRows; i++){
       for(int j=0; j<mCols; j++){
           mGridContent[i][j]= EMPTY;
       }
    }
    mGameOver=false;
    mBottom=true;
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *=getTransform();
    target.draw(mGrid, states);
    target.draw(Grid, states);
}


bool Board::checkSpace()
{
    if(mPiece.mYposition<0){
        for(int i=0; i<mPiece.MAT_SIZE; i++)
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][0][i]!=0)return false;
    }

    for(int i=0; i<mPiece.MAT_SIZE; i++)
        for(int j=0; j<mPiece.MAT_SIZE; j++){
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j]!=0){
                if(i+mPiece.mYposition<0 || i+mPiece.mYposition>=20)return false;
                if(j+mPiece.mXposition<0 || j+mPiece.mXposition>=10)return false;
                if(mGridContent[i+mPiece.mYposition][j+mPiece.mXposition]!=EMPTY)return false;
            }
        }
    return true;
}

void Board::placePiece()
{
    for(int i=0; i<mPiece.MAT_SIZE; i++)
        for(int j=0; j<mPiece.MAT_SIZE; j++){
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j]!=0){
                mGridContent[i+mPiece.mYposition][j+mPiece.mXposition]=mPiece.mType;
            }
        }
}

void Board::removePiece()
{
    for(int i=0; i<mPiece.MAT_SIZE; i++)
        for(int j=0; j<mPiece.MAT_SIZE; j++){
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j]!=0){
                mGridContent[i+mPiece.mYposition][j+mPiece.mXposition]=EMPTY;
            }
        }
}

bool Board::movePiece(int x, int y)
{
    removePiece();
    mPiece.move(x,y);
    if(!checkSpace()){
        mPiece.move(-x,-y);
        placePiece();
        return false;
    }
    placePiece();
    return true;
}

bool Board::rotatePiece()
{
    removePiece();
    mPiece.rotate();
    if(!checkSpace()){
        mPiece.rotate();
        mPiece.rotate();
        mPiece.rotate();
        placePiece();
        return false;
    }
    placePiece();
    return true;
}

bool Board::isLineFull(int y) const{
    for(int x=0; x<mCols; x++){
        if(mGridContent[y][x]==EMPTY)return false;
    }
    return true;
}

int Board::clearLines(){
    int n=0;
    for(int y=0; y<mRows; y++){
        if(isLineFull(y)){
            deleteLine(y);
            n++;
        }
    }
    return mNoLinesCompleted=n;
}

void Board::deleteLine(int y){
    while(y>0){
        for(int x=0; x<mCols; x++){
            mGridContent[y][x]=mGridContent[y-1][x];
        }
        y--;
    }
    for(int x=0; x<mCols; x++){
        mGridContent[0][x]=EMPTY;
    }
}

void Board::color()
{
    for(std::size_t i=0; i<20; ++i)
        for(std::size_t j=0; j<10; ++j)
        {
            mGrid[4*(10*i+j)].color=mPiece.mColors[mGridContent[i][j]];
            mGrid[4*(10*i+j)+1].color=mPiece.mColors[mGridContent[i][j]];
            mGrid[4*(10*i+j)+2].color=mPiece.mColors[mGridContent[i][j]];
            mGrid[4*(10*i+j)+3].color=mPiece.mColors[mGridContent[i][j]];
         }
}
