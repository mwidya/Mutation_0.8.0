//
//  videoPlayerBoard.cpp
//  Mutation_080
//
//  Created by Martin Widyanata on 01.09.14.
//
//

#include "videoPlayerBoard.h"

videoPlayerBoard::videoPlayerBoard(ofFbo *fbo){
    mFbo = fbo;
    mVideoPlayer.loadMovie("video/feet.mov");
}

void videoPlayerBoard::update(){
    mVideoPlayer.update();
    mVideoPlayer.draw(0, 0, mFbo->getWidth(), mFbo->getHeight());
}


void videoPlayerBoard::play(bool play){
    if (play) {
        mVideoPlayer.play();
    }else{
        mVideoPlayer.stop();
    }
}