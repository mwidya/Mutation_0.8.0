//
//  oneColorBoard.cpp
//  Mutation
//
//  Created by Martin Widyanata on 19.08.14.
//
//

#include "oneColorBoard.h"

oneColorBoard::oneColorBoard(ofFbo *fbo){
    mFbo = fbo;
    mFont.loadFont("vag.ttf", 50);
}

void oneColorBoard::fadeToBlack(){
    
    ofSetColor(0, 0, 0, 20);
    ofRect(0, 0, mFbo->getWidth(), mFbo->getHeight());
    
}

void oneColorBoard::drawRect(){
    
    ofSetColor(ofColor::gray);
    ofRect(0, 0, mFbo->getWidth(), mFbo->getHeight());
    
    ofSetColor(255,122,220);
    mFont.drawString("Bangin !!!", 100, 100);
    
}

void oneColorBoard::update(){
    fadeToBlack();
}