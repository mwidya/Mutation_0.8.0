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
    
    ofSetVerticalSync(true);
	ofBackground(20);
    
    // GL_REPEAT for texture wrap only works with NON-ARB textures //
    ofDisableArbTex();
    
    bFill       = true;
    bWireframe  = true;
    bDrawNormals= false;
    bDrawAxes   = false;
    bDrawLights = false;
    bInfoText   = true;
    bMousePressed   = false;
    bSplitFaces = false;
    
    if (mChannelNumber==7 || mChannelNumber==8 || mChannelNumber==2 || mChannelNumber==3) {
        box.set(mFbo->getWidth()*.5, mFbo->getHeight()*.5, mAscendantBoard->mFbo->getHeight()*.5f);
    }
    if (mChannelNumber==6 || mChannelNumber==1) {
        box.set(mFbo->getWidth()*.5, mFbo->getHeight()*.5, mDescendantBoard->mFbo->getHeight()*.5f);
    }
    
    
    mode = 0;
    
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    
    pointLight2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    pointLight2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));
    
    pointLight3.setDiffuseColor( ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f) );
    pointLight3.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f) );
    
    // shininess is a value between 0 - 128, 128 being the most shiny //
	material.setShininess( 120 );
    // the light highlight of the material //
	material.setSpecularColor(ofColor(255, 255, 255, 255));
    
//    ofSetSphereResolution(12);
    
}

void threeDBoard::update(){
    
    ofClear(0, 0, 0);
//    ofRect(0, 0, mFbo->getWidth(), mFbo->getHeight());
    
    pointLight.setPosition((mFbo->getWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(mFbo->getWidth()*.3), mFbo->getHeight()/2, 500);
    pointLight2.setPosition((mFbo->getWidth()*.5)+ cos(ofGetElapsedTimef()*.15)*(mFbo->getWidth()*.3),
                            mFbo->getHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(mFbo->getHeight()), -300);
    
    pointLight3.setPosition(
                            cos(ofGetElapsedTimef()*1.5) * mFbo->getWidth()*.5,
                            sin(ofGetElapsedTimef()*1.5f) * mFbo->getWidth()*.5,
                            cos(ofGetElapsedTimef()*.2) * mFbo->getWidth()
                            );
    
    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);
    
    if(bMousePressed) {
        spinX = spinY = 0.0f;
    }
    
    ofEnableDepthTest();
    
    ofEnableLighting();
    pointLight.enable();
    pointLight2.enable();
    pointLight3.enable();
    
	material.begin();
    
    ofSetColor(180);
    ofNoFill();
//    ofDrawSphere(mFbo->getWidth()/2, mFbo->getHeight()/2, mFbo->getWidth());
    
    // Box //
    box.setPosition(mFbo->getWidth()*.5, mFbo->getHeight()*.5, -100);
    box.rotate(spinX, 1.0, 0.0, 0.0);
    
    if(bFill) {
        ofFill();
        ofSetColor(255);
        if(mode == 3) {
            box.transformGL();
            for(int i = 0; i < ofBoxPrimitive::SIDES_TOTAL; i++ ) {
                ofPushMatrix();
                ofTranslate( boxSides[i].getNormal(0) * sin(ofGetElapsedTimef()) * 50  );
                boxSides[i].draw();
                ofPopMatrix();
            }
            box.restoreTransformGL();
        } else {
            box.draw();
        }
    }
    if(bWireframe) {
        ofNoFill();
        ofSetColor(0, 0, 0);
        if(!bFill) ofSetColor(255);
        box.setScale(1.01f);
        if(mode == 3) {
            ofSetColor(255);
        }
        box.drawWireframe();
        box.setScale(1.f);
    }
    
    material.end();
    ofDisableLighting();
    
    if(bDrawLights) {
        ofFill();
        ofSetColor(pointLight.getDiffuseColor());
        pointLight.draw();
        ofSetColor(pointLight2.getDiffuseColor());
        pointLight2.draw();
        ofSetColor(pointLight3.getDiffuseColor());
        pointLight3.draw();
    }
    
    if(bDrawNormals) {
        ofSetColor(225, 0, 255);
        box.drawNormals(20, bSplitFaces);
    }
    if(bDrawAxes) {
        box.drawAxes(box.getWidth()+30);
    }
    
    ofDisableDepthTest();
    
//    ofFill();
    
    ofSetColor(255, 0, 0);
    ofRect(1, 1, mFbo->getWidth()-2, mFbo->getHeight()-2);
    
    ofFill();
}

void threeDBoard::keyPressed(int key) {
    
	switch(key) {
		case 'f':
			ofToggleFullscreen();
			break;
        case 's':
            bFill = !bFill;
            break;
        case 'w':
            bWireframe = !bWireframe;
            break;
        case '1':
            bSplitFaces=false;
            box.setResolution(1);
            break;
        case '2':
            bSplitFaces=false;
            box.setResolution(2);
            break;
        case '3':
            bSplitFaces=false;
            box.setResolution(6);
            break;
        case '4':
            bSplitFaces=false;
            box.setResolution(10);
            break;
        case 'n':
            bDrawNormals = !bDrawNormals;
            break;
        case OF_KEY_RIGHT:
            mode++;
            if(mode > 3) mode = 0;
            break;
        case OF_KEY_LEFT:
            mode--;
            if(mode < 0) mode = 3;
            if(mode==3)
            break;
        case 'a':
            bDrawAxes = !bDrawAxes;
            break;
        case 'l':
            bDrawLights = !bDrawLights;
            break;
        case 't':
            bInfoText=!bInfoText;
            break;
        case 'z':
            bSplitFaces = !bSplitFaces;
            
            if(mode == 3) bSplitFaces = false;
            
            if(bSplitFaces) {
                
                box.setMode( OF_PRIMITIVE_TRIANGLES );
                triangles = box.getMesh().getUniqueFaces();
                box.getMesh().setFromTriangles(triangles, true);
                
            } else {
                box.setResolution( box.getResolutionWidth() );
            }
            break;
	}
    
    //
    if( mode == 3 ) {
        
        bSplitFaces = false;
        
        // if the faces were split, we can get some weird results, since we
        // might not know what the new strides were,
        // so reset the primitives by calling their setMode function
        // which recreates the mesh with the proper indicies //
        // box only supports triangles //
        box.setMode( OF_PRIMITIVE_TRIANGLES );
        
        // rebuild the box,
        box.mapTexCoords(0, 0, 5, 5);
        
        // store the box sides so that we can manipulate them later //
        for(int i = 0; i < ofBoxPrimitive::SIDES_TOTAL; i++ ) {
            boxSides[i] = box.getSideMesh( i );
        }
    }
    
}











