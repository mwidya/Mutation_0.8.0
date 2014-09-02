//
//  movingCubeBoard.cpp
//  Mutation_080
//
//  Created by Martin Widyanata on 02.09.14.
//
//

#include "movingCubeBoard.h"
#include "constants.h"

movingCubeBoard::movingCubeBoard(ofFbo *fbo){
    
    mFbo = fbo;
    
}

void movingCubeBoard::update(){
    
    ofSetColor(100, 100, 100);
    ofRect(0, 0, mFbo->getWidth(), mFbo->getHeight());
    
    // frame
    
    float lineWidth = (1 * 150 * factor) - 1; // -1 to let line disappear.
    float halfLineWidth = lineWidth/2;
    
    ofSetLineWidth(lineWidth);
    ofSetColor(232, 153, 255);//stroke color
    
    ofLine(0, halfLineWidth, mFbo->getWidth(), halfLineWidth);
    ofLine(mFbo->getWidth()-halfLineWidth, 0, mFbo->getWidth()-halfLineWidth, mFbo->getHeight());
    ofLine(mFbo->getWidth(), mFbo->getHeight()-halfLineWidth, 0, mFbo->getHeight()-halfLineWidth);
    ofLine(halfLineWidth, mFbo->getHeight(), halfLineWidth, 0);
    
}