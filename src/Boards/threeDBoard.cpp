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
    
    width = mFbo->getWidth();
    height = mFbo->getHeight();
    
    bgRect.x = 0;
    bgRect.y = 0;
    bgRect.width = width;
    bgRect.height = height;
    
    offsetZ = 0.0f;//-800.0f*factor;
    
    plane.set(width, height);
    plane.setPosition(width*.5f, height*.5f, offsetZ);
    
    /*if ( mChannelNumber==2 || mChannelNumber==3 || mChannelNumber==7 || mChannelNumber==8) {
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
    }*/
    
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f)  );
    pointLight.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f));
    
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
    
    drawThings = false;
}

void threeDBoard::drawBox(){
    
    ofClear(0);
    
    ofEnableDepthTest();
    ofEnableLighting();
    
    plane.setPosition(plane.getPosition().x, plane.getPosition().y, plane.getPosition().z + offsetZ);
    if (bPointLight) {
        pointLight.setPosition(plane.getPosition().x,
                               plane.getPosition().y,
                               plane.getPosition().z + sin(ofGetElapsedTimef()*.5f)*plane.getHeight()*1.5 + offsetZ);
        pointLight.lookAt(plane);
        pointLight.enable();
    }
    else{
        pointLight.disable();
    }
    
    if (bPointLight2) {
        pointLight2.setPosition((plane.getPosition().x)+ cos(ofGetElapsedTimef()*.15)*(plane.getWidth()*.3),
                                plane.getPosition().y + sin(ofGetElapsedTimef()*.7)*(plane.getHeight()),
                                offsetZ);
        pointLight2.lookAt(plane);
        pointLight2.enable();
    }
    else{
        pointLight2.disable();
    }
    
    if (bPointLight3) {
        pointLight3.setPosition(cos(ofGetElapsedTimef()*1.5) * plane.getPosition().x,
                                sin(ofGetElapsedTimef()*1.5f) * plane.getPosition().y,
                                cos(ofGetElapsedTimef()*.2) + offsetZ);
        pointLight3.lookAt(plane);
        pointLight3.enable();
    }
    else{
        pointLight3.disable();
    }
    
    /*box.setPosition(box.getPosition().x, box.getPosition().y, box.getPosition().z + offsetZ);
    
    if (rotate) {
     box.rotate(cos(ofGetElapsedTimef()*.6), 1.0, 0.0, 0.0);
     box.rotate(sin(ofGetElapsedTimef()*.4), 0, 1, 0);
     }
    
    if (bPointLight) {
        pointLight.setPosition((box.getPosition().x),
                               box.getPosition().y + cos(ofGetElapsedTimef())*(box.getHeight()*2),
                               box.getPosition().z + sin(ofGetElapsedTimef())*(box.getDepth()*2) + offsetZ);
        pointLight.lookAt(box);
        pointLight.enable();
    }
    else{
        pointLight.disable();
    }
    
    if (bPointLight2) {
        pointLight2.setPosition((box.getPosition().x)+ cos(ofGetElapsedTimef()*.15)*(box.getWidth()*.3),
                                box.getPosition().y + sin(ofGetElapsedTimef()*.7)*(box.getHeight()),
                                box.getDepth() + offsetZ);
        pointLight2.lookAt(box);
        pointLight2.enable();
    }
    else{
        pointLight2.disable();
    }
    
    if (bPointLight3) {
        pointLight3.setPosition(cos(ofGetElapsedTimef()*1.5) * box.getPosition().x,
                                sin(ofGetElapsedTimef()*1.5f) * box.getPosition().y,
                                cos(ofGetElapsedTimef()*.2) * box.getDepth() + offsetZ);
        pointLight3.lookAt(box);
        pointLight3.enable();
    }
    else{
        pointLight3.disable();
    }*/

    if (drawThings) {
        pointLight.draw();
        pointLight2.draw();
        pointLight3.draw();
    }
    
    offsetZ = 0.0f;
    
	material.begin();
    
    ofFill();
    ofSetColor(255);
    plane.draw();
    /*box.draw();*/
    
    material.end();
    
    ofDisableLighting();
    ofDisableDepthTest();
    ofFill();
    
}

void threeDBoard::drawBackground(){
    
    ofSetColor(0, 0, 0);
    ofRect(bgRect);
    
}

void threeDBoard::drawBounds(){
    
    float lineWidth = 20*factor;
    ofSetLineWidth(lineWidth);
    ofNoFill();
    ofSetColor(255, 0, 0);
    ofRect(lineWidth, lineWidth, mFbo->getWidth()-(lineWidth*2), mFbo->getHeight()-(lineWidth*2));
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
//        bPointLight = !bPointLight;
        sendLight();
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

void threeDBoard::tiggerAtPoint(int x_, int y_, string event_){
    if(bgRect.inside(x_, y_)){
        sendLight();
    }
}

void threeDBoard::sendLight(){
    soundPlayer.loadSound("music/fis4.aif");
    soundPlayer.play();
    bPointLight = !bPointLight;
    
}






