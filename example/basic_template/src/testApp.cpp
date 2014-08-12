#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    //Create connection
    //Node server IP address, socket to connect over and the telephone number of your flow route or IPkall
    tinyphone = new ofxTinyphoneClient("166.78.237.67",12002,"13607173355");
    
    //start the thread
    tinyphone->startThread(true,false);
    
    //add the event listeners for your custom functions
    ofAddListener(tinyphone->newCaller, this, &testApp::newCall);
    ofAddListener(tinyphone->hangup, this, &testApp::hangUpCall);
    ofAddListener(tinyphone->audioLevel, this, &testApp::receiveAudioLevel);
    ofAddListener(tinyphone->keypress, this, &testApp::receiveKeypress);
    ofAddListener(tinyphone->smsMessage, this, &testApp::receiveSMS);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

void testApp::newCall(ofxTinyphoneArgs& event){
    cout<<"newCaller event fires"<<event.toString()<<endl;
}
void testApp::hangUpCall(ofxTinyphoneArgs& event){
    cout<<"hangup event fires"<<event.toString()<<endl;
}
void testApp::receiveAudioLevel(ofxTinyphoneArgs& event){
    cout<<"audio event fires"<<event.getValue()<<endl;
}
void testApp::receiveKeypress(ofxTinyphoneArgs& event){
    cout<<"keypress event fires"<<event.getValue()<<endl;
}
void testApp::receiveSMS(ofxTinyphoneArgs& event){
    cout<<"sms event fires"<<event.toString()<<endl;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}