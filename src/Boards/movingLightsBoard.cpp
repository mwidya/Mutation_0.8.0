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
    
    float width = mFbo->getWidth();
    float height = mFbo->getHeight();
    
    float band1 = fftSmoothed[1];
    float band12 = fftSmoothed[12];
    float band38 = fftSmoothed[38];
    
    ofSetColor(0, 0, 0, 30*factor);
    ofRect(0, 0, width, height);
    
    // rect
    
    ofSetColor(255, 255, 255);//stroke color
    float rectSize = band1*0.3;//abs(sin(ofGetElapsedTimef()));
    if (rectSize<0.1) {
        rectSize=0;
    }
    cout << "rectSize = " << rectSize << endl;
    ofRect(width/2 * (rectSize * (-1) + 1), height/2 * (rectSize * (-1) + 1), width * rectSize, height * rectSize);
    
    // frame
    
    float lineWidth = (band12 * 150 * factor) - 1; // -1 to let line disappear.
    float halfLineWidth = lineWidth/2;
    
    ofSetLineWidth(lineWidth);
    ofSetColor(255, 0, 255);//stroke color
    
    ofLine(0, halfLineWidth, width, halfLineWidth);
    ofLine(width-halfLineWidth, 0, width-halfLineWidth, height);
    ofLine(width, height-halfLineWidth, 0, height-halfLineWidth);
    ofLine(halfLineWidth, height, halfLineWidth, 0);
}













