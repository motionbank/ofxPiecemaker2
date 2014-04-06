#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetLogLevel("ofxHttpUtils", OF_LOG_SILENT);
    
    ofAddListener(api.LOGIN, this, &ofApp::onAPIConnect);
    api.setup("http://piecemaker2-test.herokuapp.com/api/v1");
    api.login("SuperAdmin", "SuperAdmin");
}

void ofApp::onAPIConnect(LoginEventData& e)
{
    ofRemoveListener(api.LOGIN, this, &ofApp::onAPIConnect);
    ofLogVerbose() << "apiKey: " << api.apiKey;
    if(e.wasSuccessful())
    {
        ofAddListener(api.LIST_GROUPS, this, &ofApp::onListGroups);
        api.listGroups();
    }else
    {
        ofLogError(__func__) << "errorCode: " << e.errorCode << " reason: " << e.errorReason;
    }
    
}

void ofApp::onListGroups(GroupEventData& e)
{
    ofLogVerbose(__func__) << "groups.size(): " << e.groups.size();
    ofRemoveListener(api.LIST_GROUPS, this, &ofApp::onListGroups);
    if (e.groups.empty())
    {
        ofLogError() <<  "NO GROUPS";
    }else
    {
        ofAddListener(api.LIST_EVENTS_BETWEEN, this, &ofApp::onListEventsBetween);
        for (size_t i=0; i<e.groups.size(); i++)
        {
            Group& group    = e.groups[i];
            ofLogVerbose() << group.print();
            if(group.id == 109)
            {
                
                //Wed, 20 Apr 2011 19:30:37 GMT
                //Thu, 21 Apr 2011 09:23:57 GMT
                //219 responses
                
                api.listEventsBetween(group.id, 1303327837, 1303377837 );
                break;
                
            }
        }
    }
}

void ofApp::onListEventsBetween(PiecemakerEventData& e)
{
    ofRemoveListener(api.LIST_EVENTS_BETWEEN, this, &ofApp::onListEventsBetween);
    ofLogVerbose(__func__) << "events.size()-------------------------------->: " << e.events.size();

    if(!e.events.empty())
    {
        for (size_t i=0; i<e.events.size(); i++)
        {
            PiecemakerEvent& event    = e.events[i];
            ofLogVerbose() << event.print();
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
