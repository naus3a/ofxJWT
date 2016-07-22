#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    ofAddListener(http.newResponseEvent, this, &ofApp::newResponse);
    http.start();
    jwt.setup(&http, "admin", "admin", "http://somewebsite.com/someservice");
    ofAddListener(jwt.evToken, this, &ofApp::onToken);
}

void ofApp::newResponse(ofxHttpResponse &response){
    cout<<"content type: "<<response.contentType<<" status: "<<response.status<<" data: "<<response.responseBody<<endl;
    jwt.getResponse(response);
}

void ofApp::onToken(){
    map<string, string> data;
    data["data1"] = "blablabla";
    data["data2"] = "1";
    data["data3"] = "something";
    jwt.sendData("/someotherpath", data);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key==' '){
        jwt.askToken();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
