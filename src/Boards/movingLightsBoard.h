//
//  movingLightsBoard.h
//  Mutation_080
//
//  Created by Martin Widyanata on 30.08.14.
//
//

#ifndef __Mutation_080__movingLightsBoard__
#define __Mutation_080__movingLightsBoard__

#include <iostream>
#include "board.h"

class movingLightsBoard : public board{
public:
    movingLightsBoard(ofFbo *fbo);
    void fadeToBlack();
    void drawRect(float val);
    void drawFrame(float val);
    void update(float *fftSmoothed);
};

#endif /* defined(__Mutation_080__movingLightsBoard__) */
