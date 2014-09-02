//
//  movingCubeBoard.h
//  Mutation_080
//
//  Created by Martin Widyanata on 02.09.14.
//
//

#ifndef __Mutation_080__movingCubeBoard__
#define __Mutation_080__movingCubeBoard__

#include <iostream>
#include "ofMain.h"
#include "board.h"

class movingCubeBoard : public board{
public:
    movingCubeBoard(ofFbo *fbo);
    void update();
};

#endif /* defined(__Mutation_080__movingCubeBoard__) */
