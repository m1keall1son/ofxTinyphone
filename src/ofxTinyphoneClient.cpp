//
//  ofxTinyphoneClient.cpp
//  ofxTinyphone3
//
//  Created by Mike Allison on 4/16/13.
//
//

#include "ofxTinyphoneClient.h"
//-----------------------------

ofEvent<ofxTinyphoneArgs> ofxTinyphoneClient::newCaller;
ofEvent<ofxTinyphoneArgs> ofxTinyphoneClient::hangup;
ofEvent<ofxTinyphoneArgs> ofxTinyphoneClient::audioLevel;
ofEvent<ofxTinyphoneArgs> ofxTinyphoneClient::keypress;
ofEvent<ofxTinyphoneArgs> ofxTinyphoneClient::smsMessage;


vector<string> ofxTinyphoneClient::split(const string& str, const string& delimiters , vector<string>& tokens){
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos     = str.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos)
    {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
    return tokens;
}

ofxTinyphoneClient::ofxTinyphoneClient(string host, int port, string number){
    
    uniqueID = ofToString(ofGetElapsedTimeMillis())+ofToString((int)ofRandom(1000));
    phoneNumber = number;
    weConnected = client.setup(host, port);
    client.setMessageDelimiter("\n");
    client.send("CONNECT,"+uniqueID+","+phoneNumber+",CR");
}

string ofxTinyphoneClient::getPhoneNumber(){
    return phoneNumber;
}

void ofxTinyphoneClient::threadedFunction(){
    
    while(isThreadRunning()){
        lock();
            string message;
            string rawMessage;  
            message = client.receive();
            rawMessage = message;
            bool letsGo;
            if(message.length() > 0)letsGo = true;
            if (letsGo)
            {
                ofStringReplace(message, "{", "");
                ofStringReplace(message, "}", "");
                ofStringReplace(message, "\"", "");

                vector<string> params;
                params = split(message, ",",params);
           
                ofxTinyphoneArgs* event = new ofxTinyphoneArgs();
                
                for (int i = 0; i < params.size(); i++) {
                    vector<string> kv;
                    kv = split(params[i],":",kv);
                    
                       for(int i=0;i<kv.size();i++){
                          // cout<<"kv item: "<<kv[i]<<endl;
                       }
                    
                    if (kv[0] == "id"){
                      //  cout<<"kv[1]"<<kv[1]<<endl;
                        event->setId(kv[1]);
                      //  cout<<"event id: "<<event->getId()<<endl;
                    } else if (kv[0] == "event"){
                       // cout<<"kv[1]: "<<kv[1]<<endl;
                        event->setEventType(kv[1]);
                       // cout<<"event type:"<<event->getEventType()<<endl;
                    }else if (kv[0] == "value"){
                       // cout<<"kv[1]: "<<kv[1]<<endl;
                        event->setValue(kv[1]);
                      //  cout<<"event val: "<<event->getValue()<<endl;
                    }
                }
                switch(event->getEventType()){
					case NEW_CALLER: handleNewCaller(*event);break;
					case AUDIO_LEVEL: handleAudioLevel(*event);break;
					case KEYPRESS: handleKeypress(*event);break;
					case HANGUP: handleHangup(*event);break;
					case SMS: handleSMS(*event);break;
                }
                letsGo = false;
            }
        unlock();  
    }
    client.close();
}
void ofxTinyphoneClient::handleHangup(ofxTinyphoneArgs event) {
        ofNotifyEvent(hangup, event, this);
}

void ofxTinyphoneClient::handleKeypress(ofxTinyphoneArgs event) {
        ofNotifyEvent(keypress, event, this);
}

void ofxTinyphoneClient::handleAudioLevel(ofxTinyphoneArgs event) {
    ofNotifyEvent(audioLevel, event, this);
}

void ofxTinyphoneClient::handleSMS(ofxTinyphoneArgs event){
    vector<string> kv;
    split(event.getValue(),":",kv);
    string callerNumber = kv[0];
    string decodedURL;
    event.setCallerNumber(callerNumber);
    //create caller label, which can be used for privacy
    if (callerNumber.length()>7){
        int start = callerNumber.length()-7;
        string sb = callerNumber;
        sb.replace(start, start+3, "xxx");
        event.setCallerLabel(sb);
    }
    if (kv.size() > 1){
        try {
            Poco::URI::decode(kv[1], decodedURL);
            event.setValue(decodedURL);
        } catch (Poco::SyntaxException e) {
            // TODO Auto-generated catch block
            cerr<<e.what()<<endl;
            event.setValue(kv[1]);
        }
    }
    
    ofNotifyEvent(smsMessage, event, this);
}

void ofxTinyphoneClient::handleNewCaller(ofxTinyphoneArgs event) {
    vector<string> kv;
    split(event.getValue(),":",kv);
    string callerNumber = kv[0];
    event.setCallerNumber(callerNumber);
    //create caller label, which can be used for privacy
    if (callerNumber.length()>7){
        string sb = callerNumber;
        sb.replace(0, 6, "xxx");
        event.setCallerLabel(sb);
    }
    if (kv.size() > 1){
        vector<string> args;
        args.resize(kv.size()-1);
        for (int i = 1; i < kv.size(); i++) {
            args[i-1]=kv[i];
        }
        event.setArgs(args);
    }
     ofNotifyEvent(newCaller, event, this);
}
