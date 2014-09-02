//
//  board.cpp
//  Mutation
//
//  Created by Martin Widyanata on 29.08.14.
//
//

#include "board.h"

void board::clear(){
    ofSetColor(0, 0, 0, 5);
    ofRect(0, 0, mFbo->getWidth(), mFbo->getHeight());
}