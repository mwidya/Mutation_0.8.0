//
//  testBoard.cpp
//  Mutation
//
//  Created by Martin Widyanata on 19.08.14.
//
//

#include "testBoard.h"

testBoard::testBoard(ofFbo *fbo){
    mFbo = fbo;
}

void testBoard::update(){
    float _x = ofGetElapsedTimeMillis()/8 % (int)mFbo->getWidth();
    
    ofSetColor(50, 50, 50);
    ofRect(0, 0, mFbo->getWidth(), mFbo->getHeight());
    ofSetColor(ofColor::yellow);
    ofCircle(_x, mFbo->getHeight()*.5, 50.0);
}