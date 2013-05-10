//
//  ofxTinyphoneArgs.cpp
//  ofxTinyphone3
//
//  Created by Mike Allison on 4/16/13.
//
//

#include "ofxTinyphoneArgs.h"

ofxTinyphoneArgs::ofxTinyphoneArgs(){
    id = "";
    callerNumber = "";
    callerLabel = "";
    value = "";
    
}

string ofxTinyphoneArgs::getId() {
    return id;
}
/**
 * @param id the id to set
 */
void ofxTinyphoneArgs::setId(string newid) {
    id = newid;
}
/**
 * @return the callerNumber
 */
string ofxTinyphoneArgs::getCallerNumber() {
    return callerNumber;
}

void ofxTinyphoneArgs::setArgs(vector<string> newargs){
    args.resize(newargs.size());
    args = newargs;
}

vector<string>* ofxTinyphoneArgs::getArgs(){
    return &args;
}

void ofxTinyphoneArgs::setCallerLabel(string label){
    callerLabel = label;
}

string ofxTinyphoneArgs::getCallerLabel(){
    return callerLabel;
}

/**
 * @param callerNumber the callerNumber to set
 */
void ofxTinyphoneArgs::setCallerNumber(string caller) {
    callerNumber = caller;
}
/**
 * @return the eventType
 */
string ofxTinyphoneArgs::getEventTypeString() {
    return toString();
}

tpEventType ofxTinyphoneArgs::getEventType() {
    return eventType;
}
/**
 * @param eventType the eventType to set
 */
void ofxTinyphoneArgs::setEventType(string eType) {
    if (eType == "new_call"){
        eventType = NEW_CALLER;
    } else if (eType == "keypress"){
        eventType = KEYPRESS;
    }else if (eType == "audio_level"){
        eventType = AUDIO_LEVEL;
    }else if (eType == "hangup"){
        eventType = HANGUP;
    }else if (eType == "sms"){
        eventType = SMS;
    }
}
bool ofxTinyphoneArgs::typeEquals(tpEventType type){
    if(eventType == type) return true;
    else return false;
}

/**
 * @return the value
 */
string ofxTinyphoneArgs::getValue() {
    return value;
}
/**
 * @param value the value to set
 */
void ofxTinyphoneArgs::setValue(string val) {
    value = val;
}

string ofxTinyphoneArgs::toString(){
    string str;
    str.append("Tinyphone Event ");
    str.append(ofToString(eventType));
    str.append(": id=");
    str.append(id);
    if (eventType == NEW_CALLER || eventType == SMS){
        str += "\n   caller Number=" + callerNumber;
        str += ", caller Label=" + callerLabel + "\n";
        if (args.size() > 0){
            str += "   args=[";
            for (int i = 0; i < args.size(); i++) {
                str += "\"" + args[i] + "\",";
            }
            str = str.substr(0,str.length()-1);
            str += "]";
        }
        if (eventType == SMS){
            str += "message: " + value;
        }
    } else {
        str += ", value=" + value;
    }
    return str;
}

