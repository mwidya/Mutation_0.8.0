//
//  chessField.cpp
//  chessBoard_2
//
//  Created by Martin Widyanata on 31.05.14.
//
//

#include "chessField.h"

chessField::chessField(float x, float y, float size)
{
    this->setX(x);
    this->setY(y);
    this->setWidth(size);
    this->setHeight(size);
}

void chessField::draw()
{
    
    if (tmpColor) {
        ofSetColor(mTmpRed, mTmpGreen, mTmpBlue);
    }else{
        ofSetColor(mRed, mGreen, mBlue);
    }
    ofRect(this->getX(), this->getY(), this->getWidth(), this->getHeight());
    
}

void chessField::setColor(int r, int g, int b)
{
    mRed = r;
    mGreen = g;
    mBlue = b;
    
    tmpColor = false;
}

void chessField::setTempColor(int r, int g, int b)
{
    mTmpRed = r;
    mTmpGreen = g;
    mTmpBlue = b;
    
    tmpColor = true;
}

void chessField::playSound(int i)
{
    string path = "music/chessBoard2/audio_" + ofToString(i) + ".aif";
    mSoundPlayer.loadSound(path);
    mSoundPlayer.play();
}