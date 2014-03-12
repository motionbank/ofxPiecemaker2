//
//  ofxPiecemaker2.cpp
//  PieceMaker2Api
//
//  Created by jason van cleave on 3/10/14.
//
//

#include "ofxPiecemaker2.h"


ofxPiecemaker2::ofxPiecemaker2()
{
    apiKey = "";
}

void ofxPiecemaker2::setup()
{

}


void ofxPiecemaker2::connect(string url_, string apiKey_)
{
    this->url = url_;
    this->apiKey = apiKey_;
    LoginEventData eventData;
    eventData.response = "SUCCESS";
    ofNotifyEvent(LOGIN, eventData);
}


void ofxPiecemaker2::listEvents(int groupId)
{
    PiecemakerEventData eventData;
    vector<PiecemakerEvent> events;
    for(size_t i= 0; i<5; i++)
    {
        PiecemakerEvent event;
        
        event.id = i;
        event.utc_timestamp = ofGetTimestampString();
        event.duration = i*ofRandom(50);
        event. type = "UNDEFINED";
        event.fields[i] = ofToString("STRING VALUE" + ofToString(i));
        map<int, string> fields;
        events.push_back(event);
    }
    eventData.events = events;
    ofNotifyEvent(LIST_EVENTS, eventData);
}


void ofxPiecemaker2::createGroup(string groupTitle, string groupText)
{
    Group group;
    
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
   
    vector<Group> groups;
    /*for(size_t i= 0; i<5; i++)
    {
        Group testGroup;
        testGroup.id = i;
        testGroup.title = "testGroup title " + ofToString(i);
        testGroup.text = "testGroup text " + ofToString(i);
        groups.push_back(testGroup);
    }*/
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