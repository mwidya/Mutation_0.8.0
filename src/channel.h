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
#include "marker.h"
#include "chessBoard1.h"
#include "chessBoard2.h"
#include "movingFrameBoard.h"
#include "movingLightsBoard.h"
#include "oneColorBoard.h"
#include "threeDBoard.h"

class channel
{
    
public:
    channel(int width, int height, int glFormat, string syphonServerName);
    ~channel();
    void setMarker(int id, float x, float y, float width, float height);
    void draw(float x, float y);
    
    int mId;
    int mChannelNumber;
    marker *mMarker;
    
    ofTexture mTexture;
    ofxSyphonServer mSyphonServer;
    ofFbo mFbo;
    
    int mWidth, mHeight;
    int mGlFormat;
    string mSyphonServerName;
    
    chessBoard1 *mChessBoard1;
    chessBoard2 *mChessBoard2;
    movingFrameBoard *mMovingFrameBoard;
    movingLightsBoard *mMovingLightsBoard;
    oneColorBoard *mOneColorBoard;
    threeDBoard *mThreeDBoard;
    
};

#endif /* defined(__Mutation__channel__) */
