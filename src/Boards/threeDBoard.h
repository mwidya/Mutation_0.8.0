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
    void keyPressed(int key);
    void drawBackground();
    void drawBounds();
    void drawBox();
    
    /*ofBoxPrimitive box;*/
    ofPlanePrimitive plane;
    
    ofLight pointLight;
    ofLight pointLight2;
    ofLight pointLight3;
    bool bPointLight;
    bool bPointLight2;
    bool bPointLight3;
    bool drawThings;
    
    ofMaterial material;
    
    float width, height;
    float offsetZ;
    bool rotate;
};

#endif /* defined(__Mutation__testBoard__) */
