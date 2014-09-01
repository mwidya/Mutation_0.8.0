//
//  channel.cpp
//  Mutation
//
//  Created by Martin Widyanata on 01.08.14.
//
//

#include "channel.h"
#include "constants.h"

channel::channel(int width, int height, int glFormat, string syphonServerName){
    
    mWidth = width;
    mHeight = height;
    mGlFormat = glFormat;
    mSyphonServerName = syphonServerName;
    
    // TODO Test if new instance is created when setName is called
    mSyphonServer.setName(mSyphonServerName);
    mTexture.allocate(mWidth, mHeight, mGlFormat);
    mFbo.allocate(mWidth, mHeight, mGlFormat);
    
    mFbo.begin();
    ofClear(255, 255, 255);
    mFbo.end();
    
}

channel::~channel(){
    ofLog(OF_LOG_NOTICE, "Desructor ~channel was called");
}

void channel::setMarker(int id, float x, float y, float width, float height){

    mMarker = new marker(id, x, y, width, height);
    
}

void channel::draw(float x, float y){
    mFbo.draw(x, y);
}