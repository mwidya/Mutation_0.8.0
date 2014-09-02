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

class chessBoard2;

class chessBoard2EventArgs : public ofEventArgs {
public:
    int index;
	chessBoard2 *board;
};

class chessBoard2Events{
public:
    ofEvent<chessBoard2EventArgs> chessBoard2DidTriggerAtChessFieldIndex;
};

class chessBoard2 : public board{
    
public:
    chessBoard2(ofFbo *fbo);
    void update();
    void tiggerAtPoint(int x, int y, string event);
    chessBoard2Events events;
    
private:
    void chessBoard2DidTriggerAtChessFieldIndex(chessBoard2 *cb2, int i);
    vector<chessField*> chessFields;
    float fieldSize;
};

#endif /* defined(__Mutation__chessBoard2__) */
