//
//  ofxJWT.h
//  ofJWT
//  an addon for JSON Web Tokens https://jwt.io/
//
//  Created by enrico<nausea>viola on 6/29/16.
//
//

#pragma once
#include "ofMain.h"
#include "ofxHttpUtils.h"

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>

using namespace Poco::Net;
using namespace Poco;


class ofxJWT{
public:
    ofxJWT();
    ~ofxJWT();
    virtual void setup(ofxHttpUtils * _http, string _user, string _pass, string _url, string _tokenEP="", string _dataEP="");
    
    virtual void post(string endPoint, const ofBuffer & body);
    virtual void post(string endPoint, const ofBuffer & body, map<string, string> headers);
    
    virtual void askToken();
    virtual void sendData(string endPoint, map<string, string> data);
    
    virtual void getResponse(ofxHttpResponse & response);
    virtual string getDataField(string fieldName, ofBuffer & data);
    
    virtual bool isSuccess(int httpStatus){return (httpStatus>=200&&httpStatus<300);}
    virtual bool isToken(ofBuffer & data);
    
    virtual void setToken(ofBuffer & data);
    virtual map<string, string> makeTokenHeader();
    virtual ofBuffer makeDataBody(map<string, string> data);
    
    string getTokenEndPoint(){return tokenEndPoint;}
    string getDataEndPoint(){return dataEndPoint;}
    
    ofEvent<void> evToken;
protected:
    ofxHttpUtils * http;
    string user;
    string password;
    string url;
    string tokenEndPoint;
    string dataEndPoint;
    string token;
};