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
    
    offsetZ = 0.0f;//-5000.0f*factor;
    
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
    
//    box.rotate(-25, 1, 0, 0);
    
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    
    pointLight2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    pointLight2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));
    
    pointLight3.setDiffuseColor( ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f) );
    pointLight3.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f) );
    
	material.setShininess( 120 );
	material.setSpecularColor(ofColor(0, 0, 0, 255));
    
    rotate = false;
    
    bPointLight = false;
    bPointLight2 = false;
    bPointLight3 = false;
}

void threeDBoard::drawBox(){
    
    ofClear(0);
    
    ofEnableDepthTest();
    ofEnableLighting();
    
    box.setPosition(box.getPosition().x, box.getPosition().y, box.getPosition().z + offsetZ);
    
    if (bPointLight) {
        pointLight.setPosition((box.getPosition().x), box.getPosition().y + cos(ofGetElapsedTimef())*(box.getHeight()*2), box.getPosition().z + sin(ofGetElapsedTimef())*(box.getDepth()*2) + offsetZ);
        pointLight.lookAt(box);
        pointLight.enable();
    }
    else{
        pointLight.disable();
    }
    
    if (bPointLight2) {
        pointLight2.setPosition((box.getPosition().x)+ cos(ofGetElapsedTimef()*.15)*(box.getWidth()*.3), box.getPosition().y + sin(ofGetElapsedTimef()*.7)*(box.getHeight()), box.getDepth() + offsetZ);
        pointLight2.lookAt(box);
        pointLight2.enable();
    }
    else{
        pointLight2.disable();
    }
    
    if (bPointLight3) {
        pointLight3.setPosition(cos(ofGetElapsedTimef()*1.5) * box.getPosition().x, sin(ofGetElapsedTimef()*1.5f) * box.getPosition().y, cos(ofGetElapsedTimef()*.2) * box.getDepth() + offsetZ);
        pointLight3.lookAt(box);
        pointLight3.enable();
    }
    else{
        pointLight3.disable();
    }

    if (drawThings) {
        pointLight.draw();
        pointLight2.draw();
        pointLight3.draw();
    }
    
    offsetZ = 0.0f;
    
    if (rotate) {
        box.rotate(cos(ofGetElapsedTimef()*.6), 1.0, 0.0, 0.0);
        box.rotate(sin(ofGetElapsedTimef()*.4), 0, 1, 0);
    }
    
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
    if (drawThings) {
        drawBounds();
    }
    
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
    else if (key=='x') {
        bPointLight = !bPointLight;
    }
    else if (key=='y') {
        bPointLight2 = !bPointLight2;
    }
    else if (key=='z') {
        bPointLight3 = !bPointLight3;
    }
    else if (key=='w') {
        drawThings = !drawThings;
    }
}








