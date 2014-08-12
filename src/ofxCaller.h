//
//  ofxCaller.h
//  ofxTinyphone3
//
//  Created by Mike Allison on 4/16/13.
//
//

#ifndef __ofxTinyphone3__ofxCaller__
#define __ofxTinyphone3__ofxCaller__

#include <iostream>
#include "ofMain.h"

class ofxCaller {
public:
    string label;
    string phoneNumber;
    string uniqueID;
    float audioLevel;
    vector<string> args;
    string lastKeypress;
    
    ofxCaller();
    ofxCaller(string uniqueID, string callerNumber, string callerLabel);
    bool isCaller(string checkID);
    vector<string> getArgs();
    void setArgs(vector<string>* theseargs);
};

#endif /* defined(__ofxTinyphone3__ofxCaller__) */
