//
//  chessBoard1.h
//  Mutation
//
//  Created by Martin Widyanata on 19.08.14.
//
//

#ifndef __Mutation__chessBoard1__
#define __Mutation__chessBoard1__

#include <iostream>
#include "ofMain.h"
#include "board.h"

class chessBoard1 : public board{
    
public:
    chessBoard1(ofFbo *fbo);
    void update(float *fftSmoothed);
    
private:
    
    float rectSize = 5;
    float rectSizeMin = 5;
    float whiteMax = 255;
    int gray = 255;
    
    float stroke = 20;
    float lengthFactor = 130;
};
#endif /* defined(__Mutation__chessBoard1__) */
