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
    
    offsetZ = 0;//-1000.0f*factor;
    rotate = false;
    
    if ( mChannelNumber==2 || mChannelNumber==3 || mChannelNumber==7 || mChannelNumber==8) {
        box.set(mFbo->getWidth(), mFbo->getHeight(), mAscendantBoard->mFbo->getHeight());
        box.setPosition(mFbo->getWidth()*.5f, mFbo->getHeight()*.5f, -(mAscendantBoard->mFbo->getHeight()));
    }
    else if (mChannelNumber==1 || mChannelNumber==6) {
        box.set(mFbo->getWidth(), mFbo->getHeight(), mDescendantBoard->mFbo->getHeight());
        box.setPosition(mFbo->getWidth()*.5f, mFbo->getHeight()*.5f, -(mDescendantBoard->mFbo->getHeight()));
    }
    
    if ( mChannelNumber==2 || mChannelNumber == 7){
        box.setPosition(box.getPosition().x, box.getPosition().y, -840.0f*factor);
    }
    else if ( mChannelNumber==1 || mChannelNumber==3 || mChannelNumber==6 || mChannelNumber==8){
        box.setPosition(box.getPosition().x, box.getPosition().y, -1970.0f*factor);
    }
    
    ofSetSmoothLighting(true);
    
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    pointLight2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    pointLight2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));
    pointLight3.setDiffuseColor( ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f) );
    pointLight3.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f) );
    
	material.setShininess( 120 );
	material.setSpecularColor(ofColor(255, 255, 255, 255));
    
}

void threeDBoard::drawBox(){
    
    ofClear(0);
    
    box.setPosition(box.getPosition().x, box.getPosition().y, box.getPosition().z + offsetZ);
    offsetZ = 0.0f;
    if (rotate) {
        box.rotate(1.0, 1.0, 0.0, 0.0);
    }
    
    /*if (this->mChannelNumber == 0) {
     cout << "channelNumber 0 = " << box.getPosition().z << endl;
     }
     else if (this->mChannelNumber == 1) {
     cout << "channelNumber 1 = " << box.getPosition().z << endl;
     }
     else if (this->mChannelNumber == 2) {
     cout << "channelNumber 2 = " << box.getPosition().z << endl;
     }
     else if (this->mChannelNumber == 3) {
     cout << "channelNumber 3 = " << box.getPosition().z << endl;
     }
     else if (this->mChannelNumber == 4) {
     cout << "channelNumber 4 = " << box.getPosition().z << endl;
     }
     else if (this->mChannelNumber == 5) {
     cout << "channelNumber 5 = " << box.getPosition().z << endl;
     }
     else if (this->mChannelNumber == 6) {
     cout << "channelNumber 6 = " << box.getPosition().z << endl;
     }
     else if (this->mChannelNumber == 7) {
     cout << "channelNumber 7 = " << box.getPosition().z << endl;
     }
     else if (this->mChannelNumber == 8) {
     cout << "channelNumber 8 = " << box.getPosition().z << endl;
     }
     else if (this->mChannelNumber == 9) {
     cout << "channelNumber 9 = " << box.getPosition().z << endl;
     }*/
    
    pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);
    pointLight2.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), -300);
    pointLight3.setPosition(cos(ofGetElapsedTimef()*1.5) * ofGetWidth()*.5,sin(ofGetElapsedTimef()*1.5f) * ofGetWidth()*.5,cos(ofGetElapsedTimef()*.2) * ofGetWidth());
    
    ofEnableDepthTest();
    ofEnableLighting();
    pointLight.enable();
    pointLight2.enable();
    pointLight3.enable();
	material.begin();
    
    ofFill();
    ofSetColor(255);
    box.draw();
    
    material.end();
    ofDisableLighting();
    ofDisableDepthTest();
    ofFill();

    
}

void threeDBoard::drawBackground(){
    
    ofSetColor(0, 0, 0);
    ofRect(0, 0, mFbo->getWidth(), mFbo->getHeight());
    
}

void threeDBoard::drawBounds(){
    
    ofNoFill();
    ofSetColor(255, 0, 0);
    ofRect(1, 1, mFbo->getWidth()-2, mFbo->getHeight()-2);
    ofFill();
    
}

void threeDBoard::update(){
    
    drawBackground();
    drawBox();
    drawBounds();
    
}

void threeDBoard::keyPressed(int key){
    if (key==OF_KEY_UP) {
        offsetZ += 1.0f;
    }
    else if (key==OF_KEY_DOWN) {
        offsetZ -= 1.0f;
    }
    else if (key=='r') {
        rotate = !rotate;
    }
}








