//
//  chessBoard2.cpp
//  Mutation
//
//  Created by Martin Widyanata on 23.08.14.
//
//

#include "chessBoard2.h"

chessBoard2::chessBoard2(ofFbo *fbo){
    
    mFbo = fbo;
    fieldSize = mFbo->getWidth()/6.0;
    
    for (int i = 0; i < mFbo->getWidth() / fieldSize; i++) {
        for (int j = 0; j < mFbo->getHeight() / fieldSize; j++) {
            int randomColor = ofRandom(255);
            chessField *cf = new chessField(i*fieldSize, j*fieldSize, fieldSize);
            cf->setColor(randomColor,randomColor,randomColor);
            chessFields.push_back(cf);
        }
    }
    
    
}

void chessBoard2::update(){
    for (int i=0; i<chessFields.size(); i++) {
        chessFields[i]->draw();
    }
}

void chessBoard2::tiggerAtPoint(int x_, int y_, string event_){
    for (int i = 0; i < chessFields.size(); i++) {
        chessField *cf = chessFields[i];
        if(cf->inside(x_, y_)){
            if (event_ == "press") {
                cf->setTempColor(ofRandom(255), ofRandom(255), ofRandom(255));
                cf->playSound(i);
            }else{
                cf->setColor(cf->mRed, cf->mGreen, cf->mBlue);
            }
        }
    }
}