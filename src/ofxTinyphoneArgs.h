//
//  ofxTinyphoneArgs.h
//  ofxTinyphone3
//
//  Created by Mike Allison on 4/16/13.
//
//

#ifndef __ofxTinyphone3__ofxTinyphoneArgs__
#define __ofxTinyphone3__ofxTinyphoneArgs__

#include <iostream>
#include "ofMain.h"
enum tpEventType {
    NEW_CALLER,AUDIO_LEVEL,KEYPRESS,HANGUP,SMS
};

class ofxTinyphoneArgs {
    
public:
    
    string id;
    string callerNumber;
    string callerLabel;
    vector<string> args;
    tpEventType eventType;
    string value;
    
    ofxTinyphoneArgs();
    string getId();
    void setId(string newid);
    string getCallerNumber();
    void setArgs(vector<string> newargs);
    vector<string>* getArgs();
    void setCallerLabel(string label);
    string getCallerLabel();
    void setCallerNumber(string caller);
    string getEventTypeString();
    tpEventType getEventType();
    void setEventType(string eventType);
    bool typeEquals(tpEventType type);
    string getValue();
    void setValue(string val);
    string toString();
    
};



#endif /* defined(__ofxTinyphone3__ofxTinyphoneArgs__) */
