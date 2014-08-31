//
//  movingFrameBoard.h
//  Mutation
//
//  Created by Martin Widyanata on 18.08.14.
//
//

#ifndef __Mutation__movingFrameBoard__
#define __Mutation__movingFrameBoard__

#include <iostream>
#include "ofMain.h"
#include "board.h"
#include "constants.h"


class movingFrameBoard : public board{
    
public:
    movingFrameBoard(ofFbo *fbo);
    void update();
//    ofFbo *mFbo;
    
private:
    float mShiftX = 0.0f;
    float mShiftY = 0.0f;
    float mFadeAmnt = 15 * factor;
    float mSpeed = 8.0f;
    // TODO How to include constants.h
    float stroke = 15.0f;
    int mDirectionX = 1;
    int mDirectionY = 0;
    
};

#endif /* defined(__Mutation__movingFrameBoard__) */
