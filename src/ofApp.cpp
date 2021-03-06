#include "ofApp.h"
#include "constants.h"

// ------------------------------------ Setups & Configurations ------------------------------------
#pragma mark - Setups & Configurations

void ofApp::setupSound(){
    
//    mSoundPlayer.loadSound("music/02 Blood Stevia Sex Magik.mp3");
    mSoundPlayer.loadSound("music/Cmin_geschisse_v3_loop.wav");
//    mSoundPlayer.loadSound("music/St_able_v1.wav");
//    mSoundPlayer.loadSound("music/testPattern.mp3");
    mSoundPlayer.setLoop(true);
    
    
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
    channel2 = new channel(f2Short, f2Long, GL_RGBA32F_ARB, "F2");
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
    
    activeChannel = START_CHANNEL;
    
}

void ofApp::setupTcp(){
    
    tcpClient.setup(IP, PORT);
    tcpClient.setMessageDelimiter("\n");
	
}

void ofApp::setupBoards(){
    
    // Instantiate individual boards for each channel.
    for (int i = 0; i < channels.size(); i++) {
        channel *channel = channels[i];
        channel->mChannelNumber = i;
        
        channel->mChessBoard1 = new chessBoard1(&channel->mFbo);
        channel->mChessBoard1->mMarker = channel->mMarker;
        
        channel->mChessBoard2 = new chessBoard2(&channel->mFbo);
        channel->mChessBoard2->mMarker = channel->mMarker;
        ofAddListener(channel->mChessBoard2->events.chessBoard2DidTriggerAtChessFieldIndex,
                      this, &ofApp::chessBoard2DidTriggerAtChessFieldIndex);
        
        channel->mMovingFrameBoard = new movingFrameBoard(&channel->mFbo);
        channel->mMovingFrameBoard->mMarker = channel->mMarker;
        
        channel->mMovingLightsBoard = new movingLightsBoard(&channel->mFbo);
        channel->mMovingLightsBoard->mMarker = channel->mMarker;
        
        channel->mOneColorBoard = new oneColorBoard(&channel->mFbo);
        channel->mOneColorBoard->mMarker = channel->mMarker;
        
        channel->mThreeDBoard = new threeDBoard(&channel->mFbo);
        channel->mThreeDBoard->mChannelNumber = channel->mChannelNumber;
        channel->mThreeDBoard->mMarker = channel->mMarker;
    }
    
    for (int i = 0; i < channels.size(); i++) {
        channel *channel = channels[i];
        if (i>0) {
            channel->mThreeDBoard->mAscendantBoard = channels[i-1]->mThreeDBoard;
        }
        if (i<9) {
            channel->mThreeDBoard->mDescendantBoard = channels[i+1]->mThreeDBoard;
        }
        
        channel->mThreeDBoard->setup();
        
    }
    
    boardsArray = new bool[numberofBoards];
    setBoardsArrayTrueOnlyAtIndex(START_BOARD);
}

void ofApp::setup(){
    
    ofSetDataPathRoot("../Resources/data/");
    
    setupTcp();
    setupSound();
    setupChannels();
    setupBoards();
    
}

// ------------------------------------ Updates ------------------------------------
#pragma mark - Updates

void ofApp::updateTcp(){
    
    if (tcpClient.isConnected())
    {
        string str = tcpClient.receive();
        
        if( str.length() > 0 )
        {
            cout << "str = " << str << endl;
            parseJSONString(str);
            for (int j = 0; j < channels.size(); j++)
            {
                channel *ch = channels[j];
                if (ch->mChessBoard2->mMarker->mId == mId)
                {
                    ch->mChessBoard2->tiggerAtPoint(mScreenPoint.x, mScreenPoint.y, mEvent);
                }
            }
        }
    }
    else
    {
        deltaTime = ofGetElapsedTimeMillis() - connectTime;
		if( deltaTime > 5000 ){
			setupTcp();
			connectTime = ofGetElapsedTimeMillis();
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

void ofApp::updateBoardsForChannel(channel *channel){
    
    channel->mFbo.begin();
    
    if (boardsArray[0]==true) {
        updateChessBoard1(channel);
    }
    else if (boardsArray[1]==true) {
        updateChessBoard2(channel);
    }
    else if (boardsArray[2]==true) {
        updateMovingFrameBoard(channel);
    }
    else if (boardsArray[3]==true) {
        updateMovingLightsBoard(channel);
    }
    else if (boardsArray[4]==true) {
        updateOneColorBoard(channel);
    }
    else if (boardsArray[5]==true) {
        updateThreeDBoard(channel);
    }
    
    channel->mTexture.loadScreenData(0, 0, channel->mWidth, channel->mHeight);
    channel->mSyphonServer.publishTexture(&channel->mTexture);
    channel->mFbo.end();
    
}

void ofApp::updateChannels(){
    
    for (int i=0; i<channels.size(); i++) {
        channel *channel = channels[i];
        updateBoardsForChannel(channel);
    }
    
}

void ofApp::update(){
    
    updateSound();
    updateChannels();
    updateTcp();
    
}


// ----- board programs -----
#pragma mark board programs

void ofApp::updateChessBoard1(channel *channel){
    channel->mChessBoard1->update(fftSmoothed);
} // Board A

void ofApp::updateChessBoard2(channel *channel){
    if (channel->mChannelNumber == 4) {
        channel->mChessBoard2->update();
        channel->mChessBoard2->mMarker->draw();
    }else{
        channel->mChessBoard2->clear();
        
    }
} // Board B

void ofApp::updateMovingFrameBoard(channel *channel){
    channel->mMovingFrameBoard->update();
    
} // Board C

void ofApp::updateMovingLightsBoard(channel *channel){
    channel->mMovingLightsBoard->update(fftSmoothed);
    
} // Board D

void ofApp::updateOneColorBoard(channel *channel){
    
    if (mCount == 1) {
        if ((channel->mChannelNumber == 1) || (channel->mChannelNumber == 2) || (channel->mChannelNumber == 3)) {
            channel->mOneColorBoard->update();
        }
        else{
            channel->mOneColorBoard->clear();
        }
    }
    else if (mCount == 2) {
        if ((channel->mChannelNumber == 1) || (channel->mChannelNumber == 2) || (channel->mChannelNumber == 3) ||
            (channel->mChannelNumber == 6) || (channel->mChannelNumber == 7) || (channel->mChannelNumber == 8)) {
            channel->mOneColorBoard->update();
        }
        else{
            channel->mOneColorBoard->clear();
        }
    }
    else if (mCount == 3) {
        if ((channel->mChannelNumber == 0) || (channel->mChannelNumber == 1) || (channel->mChannelNumber == 2) ||
            (channel->mChannelNumber == 3) || (channel->mChannelNumber == 4)) {
            channel->mOneColorBoard->update();
        }
        else{
            channel->mOneColorBoard->clear();
        }
    }
    else if (mCount == 4) {
        if ((channel->mChannelNumber == 5) || (channel->mChannelNumber == 6) || (channel->mChannelNumber == 7) ||
            (channel->mChannelNumber == 8) || (channel->mChannelNumber == 9)) {
            channel->mOneColorBoard->update();
        }
        else{
            channel->mOneColorBoard->clear();
        }
    }
    else{
        if (fftSmoothed[1]>0.5) {
            if ((channel->mChannelNumber == 0) || (channel->mChannelNumber == 1)) {
                channel->mOneColorBoard->update();
            }
        }
        if (fftSmoothed[1]>1) {
            if ((channel->mChannelNumber == 2) || (channel->mChannelNumber == 3)) {
                channel->mOneColorBoard->update();
            }
        }
        if (fftSmoothed[1]>1.5) {
            if ((channel->mChannelNumber == 4) || (channel->mChannelNumber == 5)) {
                channel->mOneColorBoard->update();
            }
        }
        if (fftSmoothed[1]>2) {
            if ((channel->mChannelNumber == 6) || (channel->mChannelNumber == 7)) {
                channel->mOneColorBoard->update();
            }
        }
        if (fftSmoothed[1]>2.5) {
            if ((channel->mChannelNumber == 8) || (channel->mChannelNumber == 9)) {
                channel->mOneColorBoard->update();
            }
        }
        else{
            channel->mOneColorBoard->clear();
        }
    }
} // Board E

void ofApp::updateThreeDBoard(channel *channel){
//    if (channel->mChannelNumber == 4) {
        channel->mThreeDBoard->update();
        channel->mThreeDBoard->mMarker->draw();
//    }
    
} // Board F

// ------------------------------------ of Lifecycle ------------------------------------
#pragma mark - of Lifecycle

void ofApp::draw(){
    
    ofClear(30, 30, 30);
    
    ofSetColor(255, 255, 255);    // draw fbo without color modulation
    
    for (int i = 0; i<channels.size(); i++) {
        channel *channel = channels[i];
        if (i==activeChannel) {
            channel->draw(0,0);
        }
    }
    
    if (info) {
        ofSetColor(255,255,255,128);
        
        string tcpString = "";
        if (tcpClient.isConnected()) {
            tcpString = "TCP client is connected to ip " + ofToString(tcpClient.getIP()) + " at port: " + ofToString(tcpClient.getPort());
        }
        else{
            tcpString = "TCP client couldn't connect to ip " + ofToString(IP) + " at port: " + ofToString(PORT);
        }
        
        ofDrawBitmapString(tcpString, 10, ofGetHeight()-15);
        ofDrawBitmapString("framerate:" + ofToString(ofGetFrameRate()) , ofGetWidth()-290, ofGetHeight()-15);
        ofDrawBitmapString("seconds:" + ofToString((int)ofGetElapsedTimef()) , ofGetWidth()-100, ofGetHeight()-15);
        
        float width = (float)(ofGetWidth()) / nBandsToGet;
        for (int i = 0;i < nBandsToGet; i++){
            ofRect(i*width,ofGetHeight()-100,width,-(fftSmoothed[i] * 200));
            if ((i%5)==0) {
                ofDrawBitmapString(ofToString(i), i*width, ofGetHeight()-100+15);
            }
        }
    }
    
}

void ofApp::keyPressed(int key){
    
    if (48 <= key && key <= 57) {
        activeChannel = (key - 48); // 0 has ASCII value 48
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
    else if(key=='g'){
        setBoardsArrayTrueOnlyAtIndex(6);
    }
    
    else if(key=='v'){
        mCount = (mCount+1)%5;
    }
    
    if (key == 's') {
        if (!soundIsPlaying) {
            mSoundPlayer.play();
        }else{
            mSoundPlayer.stop();
        }
        
        soundIsPlaying = !soundIsPlaying;
    }
    
    if (key==OF_KEY_UP || key==OF_KEY_DOWN || key=='r' || key=='x' || key=='y' || key=='z' || key=='w') {
        for (int i = 0; i<channels.size(); i++) {
            channel *ch = channels[i];
            ch->mThreeDBoard->keyPressed(key);
        }
    }
    
    if (key==',') {
        info = !info;
    }
    
}

void ofApp::mousePressed(int x, int y, int button){
    
    if (activeBoard == 1) {
        for (int i = 0; i<channels.size(); i++) {
            channel *channel = channels[i];
            if (i==4) {
                channel->mChessBoard2->tiggerAtPoint(x, y, "press");
            }
        }
    }
    
    if (activeBoard == 5) {
        for (int i = 0; i<channels.size(); i++) {
            channel *channel = channels[i];
            if (i==4) {
                channel->mThreeDBoard->tiggerAtPoint(x, y, "press");
            }
        }
    }
    
}

void ofApp::mouseReleased(int x, int y, int button){
    if (activeBoard == 1) {
        for (int i = 0; i<channels.size(); i++) {
            channel *channel = channels[i];
            if (i==4) {
                channel->mChessBoard2->tiggerAtPoint(x, y, "release");
            }
        }
    }
    
}

// ------------------------------------ Channel controlling ------------------------------------
#pragma mark - Channel controlling

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

// ------------------------------------ Network Communication ------------------------------------
#pragma mark - Network Communication

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
#pragma mark - Boards

// ----- chessBoard2 delegate -----
#pragma mark chessBoard2 delegate

void ofApp::chessBoard2DidTriggerAtChessFieldIndex(chessBoard2EventArgs &arg){
    
    if (arg.index == 4) {
        setBoardsArrayTrueOnlyAtIndex(4);
        mSoundPlayer.play();
    }
    
}





























