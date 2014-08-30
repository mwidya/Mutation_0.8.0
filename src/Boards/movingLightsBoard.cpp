//
//  movingLightsBoard.cpp
//  Mutation_080
//
//  Created by Martin Widyanata on 30.08.14.
//
//

#include "movingLightsBoard.h"

movingLightsBoard::movingLightsBoard(ofFbo *fbo){
    mFbo = fbo;
}

void movingLightsBoard::update(){
    ofSetColor(255, 0, 0); //fill color
    ofRect(0, 0, mFbo->getWidth(), mFbo->getHeight());
    ofNoFill();
    ofSetLineWidth(10);
    ofSetColor(255, 255, 255);//stroke color
    ofRect(5, 5, mFbo->getWidth()-10, mFbo->getHeight()-10);
    ofFill();
}