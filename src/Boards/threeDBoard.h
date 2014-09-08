//
//  testBoard.h
//  Mutation
//
//  Created by Martin Widyanata on 19.08.14.
//
//

#ifndef __Mutation__threeDBoard__
#define __Mutation__threeDBoard__

#include <iostream>
#include "ofMain.h"
#include "board.h"

class threeDBoard : public board {
public:
    
    threeDBoard(ofFbo *fbo);
    void update();
    void setup();
    
    ofBoxPrimitive box;
    float offsetZ;
    
};

#endif /* defined(__Mutation__testBoard__) */
