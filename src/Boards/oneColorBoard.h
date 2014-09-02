//
//  oneColorBoard.h
//  Mutation
//
//  Created by Martin Widyanata on 19.08.14.
//
//

#ifndef __Mutation__oneColorBoard__
#define __Mutation__oneColorBoard__

#include <iostream>
#include "ofMain.h"
#include "board.h"

class oneColorBoard : public board{
public:
    oneColorBoard(ofFbo *fbo);
    void update();
    
private:
    ofTrueTypeFont mFont;
};

#endif /* defined(__Mutation__oneColorBoard__) */
