#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    isConnected = false;
    login();
}

void ofApp::login()
{
    ofAddListener(api.LOGIN, this, &ofApp::onAPIConnect);
    api.setup("http://piecemaker2-test.herokuapp.com/api/v1");
    // api.login("SuperAdmin", "SuperAdmin");
    api.login("test@fake.motionbank.org", "test@fake.motionbank.org");
}

void ofApp::onAPIConnect(LoginEventData& e)
{
    ofRemoveListener(api.LOGIN, this, &ofApp::onAPIConnect);
    ofLogVerbose() << "apiKey: " << api.apiKey;
    if(e.wasSuccessful())
    {
        isConnected = true;
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
        ofLogVerbose() << "NO GROUPS";
         //createRandomGroups();
    }else
    {
        for (size_t i=0; i<e.groups.size(); i++)
        {
            Group& group    = e.groups[i];
            group.print();
            api.getGroup(group.id);
            listEventsForGroup(group.id);
        }
    }
}

static const char alphanum[] =
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

char genRandom()
{
    int stringLength = sizeof(alphanum) - 1;
    return alphanum[rand() % stringLength];
};

void ofApp::createRandomGroups()
{
    ofAddListener(api.CREATE_GROUP, this, &ofApp::onGroupCreated);
    
    for (size_t i=0; i<2; i++)
    {
        string title = "title ";
        string text = "text ";
        for(unsigned int j = 0; j < 10; ++j)
        {
            title += genRandom();
            text += genRandom();
        }
        api.createGroup(title, text);
    }
    
}

void ofApp::listEventsForGroup(int groupId)
{
    ofLogVerbose(__func__) << "groupId: " << groupId;
    ofAddListener(api.LIST_EVENTS, this, &ofApp::onListEvents);
    api.listEvents( groupId );
}

void ofApp::onListEvents(PiecemakerEventData& e)
{
    ofLogVerbose(__func__) << "events.size(): " << e.events.size();
    ofRemoveListener(api.LIST_EVENTS, this, &ofApp::onListEvents);
    if(!e.events.empty())
    {
        for (size_t i=0; i<e.events.size(); i++)
        {
            PiecemakerEvent& event    = e.events[i];
            event.print();
        }
    }
    
}

void ofApp::logout()
{
    ofAddListener(api.LOGOUT, this, &ofApp::onAPIDisconnect);
    api.logout();
}

void ofApp::onAPIDisconnect(LoginEventData& e)
{
    ofRemoveListener(api.LOGIN, this, &ofApp::onAPIDisconnect);
    
    if(e.wasSuccessful())
    {
        ofLogVerbose() << "LOGOUT PASS";
        isConnected = false;
    }else
    {
        ofLogError(__func__) << "errorCode: " << e.errorCode << " reason: " << e.errorReason;
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushStyle();
    if (isConnected)
    {
        ofBackground(ofColor::green);
    }else
    {
        ofBackground(ofColor::red);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'x')
    {
        logout();
    }
    if (key == 'c')
    {
        if(!isConnected)
        {
           login();
        }
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
