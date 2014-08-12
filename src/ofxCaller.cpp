//
//  ofxCaller.cpp
//  ofxTinyphone3
//
//  Created by Mike Allison on 4/16/13.
//
//

#include "ofxCaller.h"

ofxCaller::ofxCaller(){
    lastKeypress="?";
}

ofxCaller::ofxCaller(string uniqueID, string callerNumber, string callerLabel){
    uniqueID = uniqueID;
    phoneNumber = callerNumber;
    label = callerLabel;
    lastKeypress="?";
}

bool ofxCaller::isCaller(string checkID){
    return uniqueID == checkID;
}

vector<string> ofxCaller::getArgs(){
    return args;
}

void ofxCaller::setArgs(vector<string> *theseargs){
    vector<string>& newArgs = *theseargs;
    args = newArgs;
}

