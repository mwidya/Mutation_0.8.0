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
    
    bool bFill;
    bool bWireframe;
    bool bDrawNormals;
    bool bDrawAxes;
    bool bDrawLights;
    bool bInfoText;
    bool bMousePressed;
    bool bSplitFaces;
    
    int mode;
    
    ofBoxPrimitive box;
    
    ofLight pointLight;
    ofLight pointLight2;
    ofLight pointLight3;
    ofMaterial material;
    
    // place to store the sides of the box //
    ofVboMesh boxSides[ofBoxPrimitive::SIDES_TOTAL];
    ofVboMesh deformPlane;
    ofVboMesh topCap, bottomCap, body;
    vector<ofMeshFace> triangles;
    
};

#endif /* defined(__Mutation__testBoard__) */
