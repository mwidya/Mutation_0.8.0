//
//  testBoard.h
//  Mutation
//
//  Created by Martin Widyanata on 19.08.14.
//
//

#ifndef __Mutation__testBoard__
#define __Mutation__testBoard__

#include <iostream>
#include "ofMain.h"
#include "board.h"

class testBoard : public board {
public:
    testBoard(ofFbo *fbo);
    void update();
    
};

#endif /* defined(__Mutation__testBoard__) */
