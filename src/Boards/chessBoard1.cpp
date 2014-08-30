//
//  chessBoard1.cpp
//  Mutation
//
//  Created by Martin Widyanata on 19.08.14.
//
//

#include "chessBoard1.h"

chessBoard1::chessBoard1(ofFbo *fbo){
    
    mFbo = fbo;
    
}

void chessBoard1::update(float *fftSmoothed){

    float band0 = fftSmoothed[1]*mFbo->getWidth()/25.0;
    float band12 = fftSmoothed[12] * lengthFactor * 5;
    float band38 = fftSmoothed[38] * lengthFactor;
    
    if (band0 > rectSizeMin) {
        rectSize = (int)band0;
    }

    for (int i = 0; i < mFbo->getWidth() / rectSize; i++) {
        for (int j = 0; j < mFbo->getHeight() / rectSize; j++) {
            ofSetColor(ofRandom(0, whiteMax));
            ofRect(rectSize * i, rectSize * j, rectSize, rectSize);
        }
    }

    ofSetColor(255, 0, 0, 100);
    ofRect(0, stroke, band12, stroke);

    ofSetColor(0, 0, 255, 100);
    ofRect(mFbo->getWidth()-band38, mFbo->getHeight() - stroke * 2, band38, stroke);
}