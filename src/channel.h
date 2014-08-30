//
//  channel.h
//  Mutation
//
//  Created by Martin Widyanata on 01.08.14.
//
//

#ifndef __Mutation__channel__
#define __Mutation__channel__

#include <iostream>
#include "ofMain.h"
#include "ofxSyphon.h"

class channel
{
    
public:
    channel(int width, int height, int glFormat, string syphonServerName);
    ~channel();
    
    void setMarker(int id, float x, float y, float width, float height);
    void drawMarker();
    void draw(float x, float y);
    
    int mId;
    
    ofTexture mTexture;
    ofxSyphonServer mSyphonServer;
    ofFbo mFbo;
    
    int mWidth, mHeight;
    int mGlFormat;
    string mSyphonServerName;
    
    ofImage mMarker;
    float mMarkerX, mMarkerY, mMarkerWidth, mMarkerHeight;
};

#endif /* defined(__Mutation__channel__) */
