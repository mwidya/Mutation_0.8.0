#pragma once

#include "ofMain.h"
#include "channel.h"
#include "movingFrameBoard.h"
#include "chessBoard1.h"
#include "testBoard.h"
#include "oneColorBoard.h"
#include "chessBoard2.h"
#include "movingLightsBoard.h"
#include "ofxNetwork.h"
#include "ofxJSONElement.h"

class ofApp : public ofBaseApp{
    
public:
    
    // ------------------------------------ Setups & Configurations ------------------------------------
    
    void setupArrays();
    void setupSound();
    void setupChannels();
    void setupTcpServer();
    void setupBoards();
    void setup();
    
    // ------------------------------------ Updates ------------------------------------
    
    void updateSound();
    void updateBoardsForChannel(int index);
    void updateChannels();
    void updateTcpServer();
    void update();
    
    // ------------------------------------ of Lifecycle ------------------------------------
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    // ------------------------------------ Channel controlling ------------------------------------
    
    void setBoardsArrayTrueOnlyAtIndex(int index);
    void setChannelsArrayTrueOnlyAtIndex(int index);
    void setChannelsArrayTrue();
    void setChannelsArrayFalse();
    
    // ------------------------------------ Network Communication ------------------------------------
    
    ofVec2f normalizedPointToScreenPoint(ofVec2f);
    void parseJSONString(string str);
    
    // ------------------------------------ Boards ------------------------------------
    
    void triggerChessBoard2(int x, int y, string event);
    
    // ------------------------------------ Channels ------------------------------------
    
    vector<channel*> channels;
    channel *channel0;
    channel *channel1;
    channel *channel2;
    channel *channel3;
    channel *channel4;
    channel *channel5;
    channel *channel6;
    channel *channel7;
    channel *channel8;
    channel *channel9;
    
    int numberofChannels = 10;
    bool *channelsArray;
    int numberofBoards = 6;
    bool *boardsArray;
    
    bool playAll;
    bool drawMarker;
    
    int activeChannel = -1;
    int activeBoard = -1;
    
    // ------------------------------------ Boards ------------------------------------
    
    vector<movingFrameBoard*> movingFrameBoards;
    vector<chessBoard1*> chessBoard1s;
    vector<testBoard*> testBoards;
    vector<oneColorBoard*> oneColorBoards;
    vector<chessBoard2*> chessBoard2s;
    vector<movingLightsBoard*> movingLightsBoards;
    
    // ------------------------------------ Sound Player ------------------------------------
    
    ofSoundPlayer soundPlayer;
    bool soundIsPlaying;
    float *fftSmoothed;
    int nBandsToGet;
    
    // ------------------------------------ Network Communication ------------------------------------
    
    ofxTCPServer tcpServer;
    bool tcpConnected;
    int deltaTime = 0;
    int connectTime = 0;
    
    ofxJSONElement mJsonElement;
    ofVec2f mScreenPoint;
    string mEvent;
    int mId;
    
};
