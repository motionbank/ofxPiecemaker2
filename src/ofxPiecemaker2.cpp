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
    EventData eventData("hello");
    ofNotifyEvent(eventDispatcher, eventData);
}


void ofxPiecemaker2::listGroups()
{
    if (!ensureApiKey())
    {
        return;
    }
   
    vector<PiecemakerGroup> groups;
    for(size_t i= 0; i<5; i++)
    {
        PiecemakerGroup testGroup;
        testGroup.id = i;
        testGroup.title = "testGroup title " + ofToString(i);
        testGroup.text = "testGroup text " + ofToString(i);
        groups.push_back(testGroup);
    }
    GroupEventData eventData(groups);
    eventData.groups = groups;
    ofNotifyEvent(groupEventDispatcher, eventData);
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