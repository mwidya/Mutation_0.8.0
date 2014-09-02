//
//  marker.cpp
//  Mutation_080
//
//  Created by Martin Widyanata on 02.09.14.
//
//

#include "marker.h"
#include "constants.h"

marker::marker(int id, float x, float y, float width, float height){
    mId = id;
    mX = x;
    mY = y;
    mWidth = width;
    mHeight = height;
    string path = "images/marker_" + ofToString(mId) + ".png";
    mImage.loadImage(path);
}

void marker::draw(){
    ofSetColor(255, 255, 255);
    float frame = 80*factor;
    ofRect(mX-(frame/2), mY-(frame/2), mWidth+frame, mHeight+frame);
    mImage.draw(mX, mY, mWidth, mHeight);
}