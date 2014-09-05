//
//  board.h
//  Mutation
//
//  Created by Martin Widyanata on 29.08.14.
//
//

#ifndef __Mutation__board__
#define __Mutation__board__

#include <iostream>
#include "ofMain.h"
#include "marker.h"

class board{
public:
    void clear();
    
    ofFbo *mFbo;
    marker *mMarker;
    int mChannelNumber;
    
    board *mAscendantBoard;
    board *mDescendantBoard;
};

#endif /* defined(__Mutation__board__) */
