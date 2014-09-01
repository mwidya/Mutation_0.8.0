//
//  marker.h
//  Mutation_080
//
//  Created by Martin Widyanata on 02.09.14.
//
//

#ifndef __Mutation_080__marker__
#define __Mutation_080__marker__

#include <iostream>
#include "ofMain.h"

class marker{
public:
    marker(int id, float x, float y, float width, float height);
    void draw();
    
    ofImage mImage;
    int mId;
    float mX;
    float mY;
    float mWidth;
    float mHeight;
};

#endif /* defined(__Mutation_080__marker__) */
