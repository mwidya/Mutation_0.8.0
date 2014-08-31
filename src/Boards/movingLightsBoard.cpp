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

void movingLightsBoard::update(float *fftSmoothed){
    
    float band1 = fftSmoothed[1];
    float band12 = fftSmoothed[12];
    float band38 = fftSmoothed[38];
    
    ofSetColor(0, 0, 0, 10);
    ofRect(0, 0, mFbo->getWidth(), mFbo->getHeight());
    
    // rect
    
    ofSetColor(255, 255, 255);//stroke color
    float rectSize = band1;//abs(sin(ofGetElapsedTimef()));
    cout << "rectSize = " << rectSize << endl;
    ofRect(mFbo->getWidth()/2 * (rectSize * (-1) + 1), mFbo->getHeight()/2 * (rectSize * (-1) + 1), mFbo->getWidth() * rectSize, mFbo->getHeight() * rectSize);
    
    // frame
    
    float lineWidth = (band12 * 150 * factor) - 1; // -1 to let line disappear.
    float halfLineWidth = lineWidth/2;
    
    ofSetLineWidth(lineWidth);
    ofSetColor(255, 0, 255);//stroke color
    
    ofLine(0, halfLineWidth, mFbo->getWidth(), halfLineWidth);
    ofLine(mFbo->getWidth()-halfLineWidth, 0, mFbo->getWidth()-halfLineWidth, mFbo->getHeight());
    ofLine(mFbo->getWidth(), mFbo->getHeight()-halfLineWidth, 0, mFbo->getHeight()-halfLineWidth);
    ofLine(halfLineWidth, mFbo->getHeight(), halfLineWidth, 0);
}













