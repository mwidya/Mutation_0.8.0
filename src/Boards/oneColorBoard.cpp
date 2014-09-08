//
//  oneColorBoard.cpp
//  Mutation
//
//  Created by Martin Widyanata on 19.08.14.
//
//

#include "oneColorBoard.h"
#include "constants.h"
oneColorBoard::oneColorBoard(ofFbo *fbo){
    mFbo = fbo;
    mFont.loadFont("vag.ttf", 50);
}

void oneColorBoard::update(){
    
    float val = 5;//(sin(ofGetElapsedTimef()*5)*.25f + .25f) * 128;
    
    ofSetColor(val, val*5, val);
    ofRect(0, 0, mFbo->getWidth(), mFbo->getHeight());
    
    // frame
    
    float lineWidth = (75 * factor) - 1; // -1 to let line disappear.
    float halfLineWidth = lineWidth/2;
    
    ofSetLineWidth(lineWidth);
    ofSetColor(0, 255, 0);//stroke color
    
    ofLine(0, halfLineWidth, mFbo->getWidth(), halfLineWidth);
    ofLine(mFbo->getWidth()-halfLineWidth, 0, mFbo->getWidth()-halfLineWidth, mFbo->getHeight());
    ofLine(mFbo->getWidth(), mFbo->getHeight()-halfLineWidth, 0, mFbo->getHeight()-halfLineWidth);
    ofLine(halfLineWidth, mFbo->getHeight(), halfLineWidth, 0);
    
    ofSetColor(0, 255, 0);//stroke color
    mFont.drawString("Boundries", 20, mFbo->getHeight()-20);
    
    ofSetLineWidth(1.0f);
}