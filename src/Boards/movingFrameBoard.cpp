//
//  movingFrameBoard.cpp
//  Mutation
//
//  Created by Martin Widyanata on 18.08.14.
//
//

#include "movingFrameBoard.h"

movingFrameBoard::movingFrameBoard(ofFbo *fbo){
    
    mFbo = fbo;
    
}

void movingFrameBoard::update(){
    
    ofSetColor(150, 150, 150, mFadeAmnt);
    ofRect(0, 0, mFbo->getWidth(), mFbo->getHeight());
    
    mShiftX += mSpeed*mDirectionX;
    mShiftY += mSpeed*mDirectionY;
    
    if (mShiftX <= 0 && mShiftY <= 0) {
        mDirectionX = 1;
        mDirectionY = 0;
    }
    if (mShiftX > mFbo->getWidth()-stroke && mShiftY <= 0) {
        mDirectionX = 0;
        mDirectionY = 1;
    }
    if (mShiftX > mFbo->getWidth()-stroke && mShiftY > mFbo->getHeight()-stroke) {
        mDirectionX = -1;
        mDirectionY = 0;
    }
    if (mShiftX <= 0 && mShiftY > mFbo->getHeight()-stroke) {
        mDirectionX = 0;
        mDirectionY = -1;
    }
    
    ofSetColor(255,0,255);
    ofRect(mShiftX, mShiftY, stroke, stroke);
}