//
//  chessField.h
//  chessBoard_2
//
//  Created by Martin Widyanata on 31.05.14.
//
//

#ifndef __chessBoard_2__chessField__
#define __chessBoard_2__chessField__

#include <iostream>
#import "ofMain.h"

class chessField : public ofRectangle{
    
public:
    chessField(float x, float y, float size);
    
    void update();
    void draw();
    void setColor(int r, int g, int b);
    void setTempColor(int r, int g, int b);
    void playSound(int i);
    
    bool tmpColor;
    
    int mRed;
    int mGreen;
    int mBlue;
    
    int mTmpRed;
    int mTmpGreen;
    int mTmpBlue;
    
private:
    
    ofSoundPlayer mSoundPlayer;
    
};

#endif /* defined(__chessBoard_2__chessField__) */
