//
//  movingLightsBoard.cpp
//  Mutation_080
//
//  Created by Martin Widyanata on 30.08.14.
//
//

#include "movingLightsBoard.h"
#include "constants.h"

movingLightsBoard::movingLightsBoard(ofFbo *fbo){
    mFbo = fbo;
}

void movingLightsBoard::fadeToBlack(){
    
    ofSetColor(0, 0, 0, 10);
    ofRect(0, 0, mFbo->getWidth(), mFbo->getHeight());
    
}

void movingLightsBoard::drawRect(float val){
    
    // rect
    
    ofSetColor(171, 250, 255);//stroke color
    float rectSize = val*0.3;//abs(sin(ofGetElapsedTimef()));
    if (rectSize<0.1) {
        rectSize=0;
    }
    
    ofRect(mFbo->getWidth()/2 * (rectSize * (-1) + 1), mFbo->getHeight()/2 * (rectSize * (-1) + 1), mFbo->getWidth() * rectSize, mFbo->getHeight() * rectSize);
    
}

void movingLightsBoard::drawFrame(float val){
    
    // frame
    
    float lineWidth = (val * 150 * factor) - 1; // -1 to let line disappear.
    float halfLineWidth = lineWidth/2;
    
    ofSetLineWidth(lineWidth);
    ofSetColor(232, 153, 255);//stroke color
    
    ofLine(0, halfLineWidth, mFbo->getWidth(), halfLineWidth);
    ofLine(mFbo->getWidth()-halfLineWidth, 0, mFbo->getWidth()-halfLineWidth, mFbo->getHeight());
    ofLine(mFbo->getWidth(), mFbo->getHeight()-halfLineWidth, 0, mFbo->getHeight()-halfLineWidth);
    ofLine(halfLineWidth, mFbo->getHeight(), halfLineWidth, 0);
    
}

void movingLightsBoard::update(float *fftSmoothed){
    
    float band1 = fftSmoothed[1];
    float band12 = fftSmoothed[12];
    float band38 = fftSmoothed[38];
    
    fadeToBlack();
    drawRect(band1);
    drawFrame(band12);
}













