#include "ofApp.h"
#include "constants.h"

#define START_BOARD 5

// ------------------------------------ Setups & Configurations ------------------------------------

void ofApp::setupArrays(){
    
    channelsArray = new bool[numberofChannels];
    setChannelsArrayTrue();
    boardsArray = new bool[numberofBoards];
    setBoardsArrayTrueOnlyAtIndex(START_BOARD);
    
}

void ofApp::setupSound(){
    
//    soundPlayer.loadSound("music/02 Blood Stevia Sex Magik.mp3");
//    soundPlayer.loadSound("music/Cmin_geschisse_v3.wav");
//    soundPlayer.loadSound("music/St_able_v1.wav");
    soundPlayer.loadSound("music/testPattern.mp3");
    
    
    fftSmoothed = new float[8192];
    for (int i = 0; i < 8192; i++){
        fftSmoothed[i] = 0;
    }
    
    nBandsToGet = 64;
    
}

void ofApp::setupChannels(){
    
    channel0 = new channel(f0Long, f0Short, GL_RGBA32F_ARB, "F0");
    channel0->setMarker(691, f0MarkerX, f0MarkerY, f0MarkerWidth, f0MarkerHeight);
    channels.push_back(channel0);
    channel1 = new channel(f1Long, f1Short, GL_RGBA32F_ARB, "F1");
    channel1->setMarker(268, f1MarkerX, f1MarkerY, f1MarkerWidth, f1MarkerHeight);
    channels.push_back(channel1);
    channel2 = new channel(f2Long, f2Short, GL_RGBA32F_ARB, "F2");
    channel2->setMarker(581, f2MarkerX, f2MarkerY, f2MarkerWidth, f2MarkerHeight);
    channels.push_back(channel2);
    channel3 = new channel(f3Long, f3Short, GL_RGBA32F_ARB, "F3");
    channel3->setMarker(761, f3MarkerX, f3MarkerY, f3MarkerWidth, f3MarkerHeight);
    channels.push_back(channel3);
    channel4 = new channel(f4Long, f4Short, GL_RGBA32F_ARB, "F4");
    channel4->setMarker(528, f4MarkerX, f4MarkerY, f4MarkerWidth, f4MarkerHeight);
    channels.push_back(channel4);
    channel5 = new channel(f5Long, f5Short, GL_RGBA32F_ARB, "F5");
    channel5->setMarker(286, f5MarkerX, f5MarkerY, f5MarkerWidth, f5MarkerHeight);
    channels.push_back(channel5);
    channel6 = new channel(f6Long, f6Short, GL_RGBA32F_ARB, "F6");
    channel6->setMarker(484, f6MarkerX, f6MarkerY, f6MarkerWidth, f6MarkerHeight);
    channels.push_back(channel6);
    channel7 = new channel(f7Long, f7Short, GL_RGBA32F_ARB, "F7");
    channel7->setMarker(99, f7MarkerX, f7MarkerY, f7MarkerWidth, f7MarkerHeight);
    channels.push_back(channel7);
    channel8 = new channel(f8Long, f8Short, GL_RGBA32F_ARB, "F8");
    channel8->setMarker(222, f8MarkerX, f8MarkerY, f8MarkerWidth, f8MarkerHeight);
    channels.push_back(channel8);
    channel9 = new channel(f9Long, f9Short, GL_RGBA32F_ARB, "F9");
    channel9->setMarker(903, f9MarkerX, f9MarkerY, f9MarkerWidth, f9MarkerHeight);
    channels.push_back(channel9);
    
}

void ofApp::setupTcpServer(){
    
    tcpConnected = tcpServer.setup(PORT);
    tcpServer.setMessageDelimiter("\n");
	
}

void ofApp::setupBoards(){
    // Instantiate individual boards for each channel.
    for (int i = 0; i < channels.size(); i++) {
        channel *channel = channels[i];
        
        movingFrameBoard *mfb = new movingFrameBoard(&channel->mFbo);
        mfb->mId = channel->mId;
        movingFrameBoards.push_back(mfb);
        
        chessBoard1 *cb1 = new chessBoard1(&channel->mFbo);
        cb1->mId = channel->mId;
        chessBoard1s.push_back(cb1);
        
        testBoard *tb = new testBoard(&channel->mFbo);
        tb->mId = channel->mId;
        testBoards.push_back(tb);
        
        oneColorBoard *ocb = new oneColorBoard(&channel->mFbo);
        ocb->mId = channel->mId;
        oneColorBoards.push_back(ocb);
        
        chessBoard2 *cb2 = new chessBoard2(&channel->mFbo);
        cb2->mId = channel->mId;
        chessBoard2s.push_back(cb2);
        
        movingLightsBoard *mlb = new movingLightsBoard(&channel->mFbo);
        mlb->mId = channel->mId;
        movingLightsBoards.push_back(mlb);
    }
}

void ofApp::setup(){
    
    setupTcpServer();
    setupArrays();
    setupSound();
    setupChannels();
    setupBoards();
    
}

// ------------------------------------ Updates ------------------------------------

void ofApp::updateTcpServer(){
    
    for(unsigned int i = 0; i <  (unsigned int)tcpServer.getLastID(); i++){
        
        if( !tcpServer.isClientConnected(i) ) {
            continue;
        }
        
        string msgRx = tcpServer.receive(i);
        
        if (msgRx.length() > 0) {
            
            parseJSONString(msgRx);
            
            for (int j = 0; j < chessBoard2s.size(); j++) {
                chessBoard2 *cb2 = chessBoard2s[j];
                if ((cb2->mId == mId) && (activeBoard == 4)) {
                    cb2->tiggerAtPoint(mScreenPoint.x, mScreenPoint.y, mEvent);
                }
            }
        }
    }
}

void ofApp::updateSound(){
    ofSoundUpdate();
    
    float * val = ofSoundGetSpectrum(nBandsToGet);
    
    for (int i = 0;i < nBandsToGet; i++){
        
        fftSmoothed[i] *= 0.96f;
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
        
    }
}

void ofApp::updateBoardsForChannel(int index){
    
    if (boardsArray[0]==true) {
        chessBoard1s[index]->update(fftSmoothed);
    }
    else if (boardsArray[1]==true) {
        movingFrameBoards[index]->update();
    }
    else if (boardsArray[2]==true) {
        testBoards[index]->update();
    }
    else if (boardsArray[3]==true) {
        oneColorBoards[index]->update();
    }
    else if (boardsArray[4]==true) {
        chessBoard2s[index]->update();
    }
    else if (boardsArray[5]==true) {
        movingLightsBoards[index]->update(fftSmoothed);
    }
    
}

void ofApp::updateChannels(){
    
    // TODO update channel(s) with activeChannel var?
    for (int i=0; i<channels.size(); i++) {
        
        channel *channel = channels[i];
        
        channel->mFbo.begin();
        
        if (channelsArray[i]) {
            updateBoardsForChannel(i);
        }
        else{
            ofClear(0, 0, 0);
        }
        
        if (drawMarker) {
            channel->drawMarker();
        }
        channel->mTexture.loadScreenData(0, 0, channel->mWidth, channel->mHeight);
        channel->mSyphonServer.publishTexture(&channel->mTexture);
        
        channel->mFbo.end();
    }
    
}

void ofApp::update(){
    
    updateSound();
    updateTcpServer();
    updateChannels();
    
}

// ------------------------------------ of Lifecycle ------------------------------------

void ofApp::draw(){
    
    ofClear(30, 30, 30);
    
    ofSetColor(255, 255, 255);    // draw fbo without color modulation
    
    if (activeChannel > -1) {
        channel *channel = channels[activeChannel];
        channel->draw(0,0);
    }
    
    ofDrawBitmapString("seconds:" + ofToString((int)ofGetElapsedTimef()) , ofGetWidth()-90, ofGetHeight()-15);
    
    if (tcpConnected) {
        string str = "TCP server is online at port: " + ofToString(tcpServer.getPort()) + ", clients: " + ofToString(tcpServer.getNumClients());
        ofDrawBitmapString(str, 10, ofGetHeight()-15);
        
        for(unsigned int i = 0; i <  (unsigned int)tcpServer.getLastID(); i++){
            if( !tcpServer.isClientConnected(i) ) {
                continue;
            }else{
                string str = "TCP client with IP " + ofToString(tcpServer.getClientIP(i))+" is connected.";
                ofDrawBitmapString(str, 10, ofGetHeight()-(15*(i+2)));
            }
        }
    }
}

void ofApp::keyPressed(int key){
    
    if (48 <= key && key <= 57) {
        setChannelsArrayTrueOnlyAtIndex(key - 48); // 0 has ASCII value 48
    }
    
    if (key=='a') {
        setBoardsArrayTrueOnlyAtIndex(0);
    }
    else if(key=='b'){
        setBoardsArrayTrueOnlyAtIndex(1);
    }
    else if(key=='c'){
        setBoardsArrayTrueOnlyAtIndex(2);
    }
    else if(key=='d'){
        setBoardsArrayTrueOnlyAtIndex(3);
    }
    else if(key=='e'){
        setBoardsArrayTrueOnlyAtIndex(4);
    }
    else if(key=='f'){
        setBoardsArrayTrueOnlyAtIndex(5);
    }
    
    if(key=='m'){
        drawMarker = !drawMarker;
    }
    
    if(key=='q'){
        playAll = !playAll;
        if (playAll) {
            setChannelsArrayTrue();
        }else{
            setChannelsArrayFalse();
        }
    }
    
    if (key == 's') {
        if (!soundIsPlaying) {
            soundPlayer.play();
        }else{
            soundPlayer.stop();
        }
        
        soundIsPlaying = !soundIsPlaying;
    }
    
}

void ofApp::mousePressed(int x, int y, int button){
    
    triggerChessBoard2(x, y, "press");
    
}

void ofApp::mouseReleased(int x, int y, int button){
    
    triggerChessBoard2(x, y, "release");
    
}

// ------------------------------------ Channel controlling ------------------------------------

void ofApp::setBoardsArrayTrueOnlyAtIndex(int index){
    for (int i = 0; i < numberofBoards; i++) {
        if (i==index) {
            boardsArray[index]=true;
        }else{
            boardsArray[i]=false;
        }
    }
    activeBoard = index;
}

void ofApp::setChannelsArrayTrueOnlyAtIndex(int index){
    for (int i = 0; i < numberofChannels; i++) {
        if (i==index) {
            channelsArray[index]=true;
        }else{
            channelsArray[i]=false;
        }
    }
    activeChannel = index;
}

void ofApp::setChannelsArrayTrue(){
    for (int i = 0; i < numberofChannels; i++) {
        channelsArray[i]=true;
    }
    activeChannel = 0;
}

void ofApp::setChannelsArrayFalse(){
    for (int i = 0; i < numberofChannels; i++) {
        channelsArray[i]=false;
    }
    activeChannel = -1;
}

// ------------------------------------ Network Communication ------------------------------------

ofVec2f ofApp::normalizedPointToScreenPoint(ofVec2f normalizedPoint){
    ofVec2f point;
    
    point.x = normalizedPoint.x * ofGetWidth();
    point.y = normalizedPoint.y * ofGetHeight();
    
    return point;
}

void ofApp::parseJSONString(string str){
    
    mJsonElement = ofxJSONElement(str);
    
    mEvent = mJsonElement["event"].asString();
    mId = mJsonElement["id"].asInt();
    
    float x = mJsonElement["x"].asFloat();
    float y = mJsonElement["y"].asFloat();
    mScreenPoint = normalizedPointToScreenPoint(ofVec2f(x, y));
    
    
}

// ------------------------------------ Boards ------------------------------------

void ofApp::triggerChessBoard2(int x, int y, string event){
    
    if (activeBoard == 4) {                                         // 4 is the chessboard. TODO automate this process, so that it's not
        chessBoard2s[activeChannel]->tiggerAtPoint(x, y, event);    // necessary to lookup the index manually.
    }
    
}





























