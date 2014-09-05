#pragma once

#include "ofMain.h"
#include "channel.h"
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
    void updateTcpServer();
    void updateBoardsForChannel(channel *channel);
    void updateChannels();
    void update();
    
    void updateChessBoard1(channel *channel);
    void updateChessBoard2(channel *channel);
    void updateMovingFrameBoard(channel *channel);
    void updateMovingLightsBoard(channel *channel);
    void updateOneColorBoard(channel *channel);
    void updateThreeDBoard(channel *channel);
    
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
    
    void chessBoard2DidTriggerAtChessFieldIndex(chessBoard2EventArgs &args);
    void triggerChessBoard2(int x, int y, string event);
    bool playVideo;
    int mCount;
    
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
    int numberofBoards = 7;
    bool *boardsArray;
    
    bool playAll;
    bool drawMarker;
    
    int activeChannel = -1;
    int activeBoard = -1;
    
    // ------------------------------------ Sound Player ------------------------------------
    
    ofSoundPlayer mSoundPlayer;
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
