//
//  ofxPiecemaker2.cpp
//  PieceMaker2Api
//
//  Created by jason van cleave on 3/10/14.
//
//

#define __func__ __PRETTY_FUNCTION__

#include "ofxPiecemaker2.h"
#include "Poco/DateTimeFormatter.h"



string ofxPiecemaker2::printResponse(ofxHttpResponse response)
{
    stringstream responseString;
    responseString << "status: "            << response.status          << "\n";
    responseString << "reasonForStatus: "   << response.reasonForStatus << "\n";
    responseString<< "contentType: "        << response.contentType     << "\n";
    responseString << "responseBody: "      << response.responseBody    << "\n";
    
    string timeFormat = "%Y-%m-%d-%H-%M-%S-%i";
    string timestampString = Poco::DateTimeFormatter::format(response.timestamp, timeFormat);
    responseString << "timestamp: " << timestampString << "\n";
    
    return responseString.str();
}

ofxPiecemaker2::ofxPiecemaker2()
{
    apiKey = "";
}

void ofxPiecemaker2::setup()
{

}
void ofxPiecemaker2::onHTTPResponse(ofxHttpResponse& response)
{
    ofLogVerbose(__func__) << printResponse(response);
}

void ofxPiecemaker2::onLoginResponse(ofxHttpResponse& response)
{
    ofRemoveListener(httpUtils.newResponseEvent, this, &ofxPiecemaker2::onLoginResponse);
     ofLogVerbose(__func__) << printResponse(response);
    ofxJSONElement parser;
    parser.parse(ofToString(response.responseBody));
    
    this->apiKey = parser["api_access_key"].asString();
    
    whoAmI();
    LoginEventData eventData;
    eventData.setResponse(response);
    ofNotifyEvent(LOGIN, eventData);
}

void ofxPiecemaker2::login(string userEmail, string userPassword)
{
    ofAddListener(httpUtils.newResponseEvent, this, &ofxPiecemaker2::onLoginResponse);
    ofxHttpForm form;
	form.action = url + "/user/login";
	form.method = OFX_HTTP_POST;
    form.addFormField( "token",    apiKey );
    form.addFormField( "email",    userEmail );
    form.addFormField( "password", userPassword );
	httpUtils.addForm(form);

}
void ofxPiecemaker2::connect(string url_, string apiKey_)
{
    this->url = url_;
    this->apiKey = apiKey_;
    //ofRemoveListener(httpUtils.newResponseEvent, this, &ofxPiecemaker2::onHTTPResponse);
    
	httpUtils.start();
    
    
    /**/
}
void ofxPiecemaker2::onWhoAmIResponse(ofxHttpResponse& response)
{
    ofRemoveListener(httpUtils.newResponseEvent, this, &ofxPiecemaker2::onWhoAmIResponse);
    ofLogVerbose(__func__) << printResponse(response);
}
void ofxPiecemaker2::whoAmI()
{
    ofLogVerbose(__func__) << " START";
    
    ofAddListener(httpUtils.newResponseEvent, this, &ofxPiecemaker2::onWhoAmIResponse);
    ofxHttpForm form;
	form.action = url + "/user/me";
	form.method = OFX_HTTP_GET;
    httpUtils.customHeaders["X-Access-Key"] = apiKey;
	httpUtils.addForm(form);
    
    ofLogVerbose(__func__) << " END";
}

void ofxPiecemaker2::listEvents(int groupId)
{
   ofLogVerbose(__func__) << " START";
    
    ofLogVerbose(__func__) << "groupId: " << groupId;
    ofAddListener(httpUtils.newResponseEvent, this, &ofxPiecemaker2::onListEventsResponse);
    ofxHttpForm form;
	form.action = url + "/group/" + ofToString(groupId) + "/events";
	form.method = OFX_HTTP_GET;
    httpUtils.customHeaders["X-Access-Key"] = apiKey;
	httpUtils.addForm(form);
    ofLogVerbose(__func__) << "form.action: " << form.action;
    ofLogVerbose(__func__) << " END";
   
}

void ofxPiecemaker2::onListEventsResponse(ofxHttpResponse& response)
{
    ofRemoveListener(httpUtils.newResponseEvent, this, &ofxPiecemaker2::onListEventsResponse);
    ofLogVerbose(__func__) << printResponse(response);
    ofxJSONElement parser;
    parser.parse(ofToString(response.responseBody));
#if 0
    PiecemakerEventData eventData;
    vector<PiecemakerEvent> events;
    if(parser.isArray())
    {
        ofLogVerbose(__func__) << "isArray(): " << parser.isArray() << " size " << parser.size();
        for(size_t i= 0; i<parser.size(); i++)
        {
            PiecemakerEvent event;
            
            event.id = parser["id"].asInt();
            event.title = parser["title"].asString();
            event.event_group_id = parser["event_group_id"].asInt();
            event.utc_timestamp = parser["created_at"].asString();
            event.duration = i*ofRandom(50);
            event. type = "UNDEFINED";
            event.fields[i] = ofToString("STRING VALUE" + ofToString(i));
            map<int, string> fields;
            events.push_back(event);
        }
    }
    "id":11,"title":"Test group","text":"... with a fancy description","created_at":"2013-12-19 15:23:19 +0000","created_by_user_id":3
    ofLogVerbose(__func__) << "isObject(): " << parser.isObject();
#endif
    // ofLogVerbose(__func__) << "location: " << response.location;
    /*response.status; 				// return code for the response ie: 200 = OK
     response.reasonForStatus;		// text explaining the status
     ofBuffer responseBody;		// the actual response
     response.contentType;			// the mime type of the response
     Poco::Timestamp timestamp;		// time of the response
     response.url;
     vector<Poco::Net::HTTPCookie> cookies;
     response.location;*/
    
    //httpUtils.stop();
    /*
   
    
    eventData.events = events;
    ofNotifyEvent(LIST_EVENTS, eventData);*/
    
}


void ofxPiecemaker2::createGroup(string groupTitle, string groupText)
{
    Group group;
    group.id = ofRandom(10);

    //TODO Check for empty?
    group.title = groupTitle;
    group.text  = groupText;
    
    vector<Group> groups;
    groups.push_back(group);
    GroupEventData eventData(groups);
    ofNotifyEvent(CREATE_GROUP, eventData);
}

void ofxPiecemaker2::listGroups()
{
    if (!ensureApiKey())
    {
        return;
    }
    ofLogVerbose(__func__) << " START";
    ofAddListener(httpUtils.newResponseEvent, this, &ofxPiecemaker2::onListGroupsResponse);
    ofxHttpForm form;
	form.action = url + "/groups";
	form.method = OFX_HTTP_GET;
    httpUtils.customHeaders["X-Access-Key"] = apiKey;
	httpUtils.addForm(form);
    ofLogVerbose(__func__) << "form.action: " << form.action;
    ofLogVerbose(__func__) << " END";
    /*
    
    for(size_t i= 0; i<5; i++)
    {
        Group testGroup;
        testGroup.id = i;
        testGroup.title = "testGroup title " + ofToString(i);
        testGroup.text = "testGroup text " + ofToString(i);
        groups.push_back(testGroup);
    }*/
    
}

void ofxPiecemaker2::onListGroupsResponse(ofxHttpResponse& response)
{
    ofRemoveListener(httpUtils.newResponseEvent, this, &ofxPiecemaker2::onListGroupsResponse);
    ofLogVerbose(__func__) << "status: " << response.status;
    ofLogVerbose(__func__) << "reasonForStatus: " << response.reasonForStatus;
    ofLogVerbose(__func__) << "contentType: " << response.contentType;
    ofLogVerbose(__func__) << "responseBody: " << response.responseBody; //e.g {"api_access_key":"0310XLHGylURCquA"}
    ofxJSONElement parser;
    parser.parse(ofToString(response.responseBody));
    /*
    string id = parser["id"].asString();
    string title = parser["title"].asString();
    string text = parser["text"].asString();
    string created_at = parser["created_at"].asString();
    string created_by_user_id = parser["created_by_user_id"].asString();*/
        string timeFormat = "%Y-%m-%d-%H-%M-%S-%i";
    string timestampString = Poco::DateTimeFormatter::format(response.timestamp, timeFormat);
    ofLogVerbose(__func__) << "timestamp: " << timestampString;
    
    vector<Group> groups;
    /*  "id": 11,
     "title": "Test group",
     "text": "... with a fancy description",
     "created_at": "2013-12-19 15:23:19 +0000",
     "created_by_user_id": 3*/
    GroupEventData eventData(groups);
    eventData.groups = groups;
    ofNotifyEvent(LIST_GROUP, eventData);
    
    
}

#pragma private functions
bool ofxPiecemaker2::ensureApiKey()
{
    if (!apiKey.empty())
    {
        
        return true;
    }
    ofLogError() << "API Key is empty:" << apiKey;
    return false;
}