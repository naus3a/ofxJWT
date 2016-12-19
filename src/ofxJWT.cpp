//
//  ofxJWT.cpp
//  ofJWT
//  an addon for JSON Web Tokens https://jwt.io/
//
//  Created by enrico<nausea>viola on 6/29/16.
//
//

#include "ofxJWT.h"

ofxJWT::ofxJWT(){
    http = NULL;
}

ofxJWT::~ofxJWT(){
    http = NULL;
}

void ofxJWT::setup(ofxHttpUtils * _http, string _user, string _pass, string _url, string _tokenEP, string _dataEP){
    http=_http;
    user=_user;
    password=_pass;
    url=_url;
    tokenEndPoint = _tokenEP;
    dataEndPoint = _dataEP;
}

void ofxJWT::post(string endPoint, const ofBuffer & body){
    http->postData(url+endPoint, body, "application/json");
}

void ofxJWT::post(string endPoint, const ofBuffer &body, map<string, string> headers){
    http->postData(url+endPoint, body, headers);
}

void ofxJWT::askToken(){
    cout<<"Asking Token:"<<endl;
    ofBuffer body;
    std::stringstream ss;
    ss << "{\n";
    ss << " \"login\":\""<<user<<"\",\n";
    ss << " \"password\":\""<<password<<"\"\n";
    ss << "}\n";
    string s = ss.str();
    cout<<s<<endl;
    body.set(s.c_str(), s.size());
    post(tokenEndPoint, body);
}

void ofxJWT::sendData(string endPoint, map<string, string> data){
    ofBuffer body = makeDataBody(data);
    post(endPoint,body,makeTokenHeader());
}

string ofxJWT::getDataField(string fieldName, ofBuffer & data){
    string rs = "";
    string s = data.getFirstLine();
    size_t found = s.find("\""+fieldName+"\"");
    if(found!=string::npos){
        size_t start = found+fieldName.size()+2;
        string ss = s.substr(start, s.size()-start);
        vector<string> sv = ofSplitString(ss, ",");
        if(sv.size()>0){
            rs = sv[0].substr(2, sv[0].size()-3);
        }
    }
    return rs;
}

bool ofxJWT::isToken(ofBuffer & data){
    string s = data.getFirstLine();
    return s.substr(0,22)=="{\"success\":true,\"JWT\":";
}

void ofxJWT::setToken(ofBuffer & data){
    string s = data.getFirstLine();
    int sz = s.size()-23;
    string s0 = s.substr(23,sz);
    vector<string> sTok = ofSplitString(s0,"\"");
    token = sTok[0];
}

map<string, string> ofxJWT::makeTokenHeader(){
    map<string, string> hdr;
    hdr["x-access-token"] = token;
    return hdr;
}

ofBuffer ofxJWT::makeDataBody(map<string, string> data){
    ofBuffer body;
    std::stringstream ss;
    string s = ss.str();
    ss << "{\n";
    for(std::map<string, string>::iterator it=data.begin(); it!=data.end(); ++it){
        ss<<"\""<<it->first<<"\":\""<<it->second<<"\",\n";
    }
    ss << "}\n";
    body.set(s.c_str(),s.size());
    return body;
}

void ofxJWT::getResponse(ofxHttpResponse & response){
    if(isSuccess(response.status)){
        if(isToken(response.responseBody)){
            setToken(response.responseBody);
            ofNotifyEvent(evToken);
        }
    }
}