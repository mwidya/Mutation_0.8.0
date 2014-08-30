//
//  chessBoard2.h
//  Mutation
//
//  Created by Martin Widyanata on 23.08.14.
//
//

#ifndef __Mutation__chessBoard2__
#define __Mutation__chessBoard2__

#include <iostream>
#include "ofMain.h"
#include "chessField.h"
#include "board.h"

class chessBoard2 : public board{
    
public:
    chessBoard2(ofFbo *fbo);
    void update();
    void tiggerAtPoint(int x, int y, string event);
    
private:
    vector<chessField*> chessFields;
    float fieldSize;
};

#endif /* defined(__Mutation__chessBoard2__) */
