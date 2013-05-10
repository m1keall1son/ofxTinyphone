//
//  ofxTinyphoneClient.h
//  ofxTinyphone3
//
//  Created by Mike Allison on 4/16/13.
//  Based on the Tinyphone Java Client by Chris Kiarella https://github.com/itp-redial/tinyphone-javaclient
//

#ifndef __ofxTinyphone3__ofxTinyphoneClient__
#define __ofxTinyphone3__ofxTinyphoneClient__

#include <iostream>
#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxTinyphoneArgs.h"
#include "Poco/URI.h"

class ofxTinyphoneClient : public ofThread{
public:
    ofxTCPClient client;

    float counter;
    int connectTime;
    int deltaTime;
    bool weConnected;
    
    string phoneNumber;
    string uniqueID;
    
    ofxTinyphoneClient();
    ofxTinyphoneClient(string host, int port, string number);
    string getPhoneNumber();
    void threadedFunction();
    vector<string> split(const string& str, const string& delimiters , vector<string>& tokens);
    
    static ofEvent<ofxTinyphoneArgs> newCaller;
    static ofEvent<ofxTinyphoneArgs> hangup;
    static ofEvent<ofxTinyphoneArgs> audioLevel;
    static ofEvent<ofxTinyphoneArgs> keypress;
    static ofEvent<ofxTinyphoneArgs> smsMessage;
    
private:
    void handleHangup(ofxTinyphoneArgs event);
    void handleKeypress(ofxTinyphoneArgs event);
    void handleAudioLevel(ofxTinyphoneArgs event);
    void handleSMS(ofxTinyphoneArgs event);
    void handleNewCaller(ofxTinyphoneArgs event);
};
#endif /* defined(__ofxTinyphone3__ofxTinyphoneClient__) */
