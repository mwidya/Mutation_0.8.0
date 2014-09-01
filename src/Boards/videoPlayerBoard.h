//
//  videoPlayerBoard.h
//  Mutation_080
//
//  Created by Martin Widyanata on 01.09.14.
//
//

#ifndef __Mutation_080__videoPlayerBoard__
#define __Mutation_080__videoPlayerBoard__

#include <iostream>
#include "ofMain.h"
#include "board.h"

class videoPlayerBoard : public board{
public:
    videoPlayerBoard(ofFbo *fbo);
    void update();
    void play(bool play);
    
    ofVideoPlayer mVideoPlayer;
};

#endif /* defined(__Mutation_080__videoPlayerBoard__) */
