//
//  testBoard.cpp
//  Mutation
//
//  Created by Martin Widyanata on 19.08.14.
//
//

#include "threeDBoard.h"
#include "constants.h"

threeDBoard::threeDBoard(ofFbo *fbo){
    
    mFbo = fbo;
    
}

void threeDBoard::setup(){
    
    float width = mFbo->getWidth();
    float height = mFbo->getHeight();
    
    if ( mChannelNumber==2 || mChannelNumber==3 || mChannelNumber==7 || mChannelNumber==8) {
        box.set(width, height, mAscendantBoard->mFbo->getHeight());
        box.setPosition(width*.5f, height*.5f, -(mAscendantBoard->mFbo->getHeight()));
    }
    if (mChannelNumber==1 || mChannelNumber==6) {
        box.set(width, height, mDescendantBoard->mFbo->getHeight());
        box.setPosition(width*.5f, height*.5f, -(mDescendantBoard->mFbo->getHeight()));
    }
    
}

void threeDBoard::update(){
    
    ofSetColor(255, 255, 255);
    box.draw();
    ofSetColor(0, 0, 0);
    box.drawWireframe();
    
    ofNoFill();
    ofSetColor(255, 0, 0);
    ofRect(1, 1, mFbo->getWidth()-2, mFbo->getHeight()-2);
    ofFill();
    
}










