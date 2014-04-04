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
        createTestGroup();
    }else
    {
        ofLogError(__func__) << "errorCode: " << e.errorCode << " reason: " << e.errorReason;
    }
    
}

void ofApp::createTestGroup(){
    ofAddListener(api.CREATE_GROUP, this, &ofApp::onGroupCreated);
    
    string title = "test group ";
    string text = "";
    api.createGroup(title, text);
}

void ofApp::onGroupCreated(GroupEventData& e)
{
    ofLogVerbose() << "onGroupCreated e.groups.size(): " << e.groups.size();
    ofRemoveListener(api.CREATE_GROUP, this, &ofApp::onGroupCreated);
    if (!e.groups.empty())
    {
        Group& group = e.groups[0];
        groupToDelete = group;
        ofLogVerbose() << group.print();
        
        PiecemakerEvent pieceMakerEvent;
        pieceMakerEvent.utc_timestamp = (long)Poco::LocalDateTime().utcTime();
       // pieceMakerEvent.title =
        pieceMakerEvent.type = "test-type-OF";
        pieceMakerEvent.duration = 3000;
        
        EventField eventField;
        eventField.id = "title";
        eventField.value = "This is a test marker ...";
        pieceMakerEvent.fields.push_back(eventField);
        
        ofAddListener(api.CREATE_EVENT, this, &ofApp::onCreateEvent);
        api.createEvent(group.id, pieceMakerEvent);
    }
    
}
void ofApp::onCreateEvent(PiecemakerEventData& e)
{
    ofLogVerbose(__func__) << "e.events size: " << e.events.size();
    ofRemoveListener(api.CREATE_EVENT, this, &ofApp::onCreateEvent);
    if (!e.events.empty())
    {
        PiecemakerEvent& pieceMakerEvent = e.events[0];
        pieceMakerEventToFail = pieceMakerEvent;
        ofLogVerbose() << pieceMakerEvent.print();
        
        ofAddListener(api.DELETE_GROUP, this, &ofApp::onGroupDeleted);
        api.deleteGroup(pieceMakerEvent.event_group_id);
    }
}

void ofApp::onGroupDeleted(GroupEventData& e)
{
    ofLogVerbose() << "onGroupDeleted e.groups.size(): " << e.groups.size();

    if (!e.groups.empty())
    {
        Group& group = e.groups[0];
        ofLogVerbose() << group.print();
        ofLogVerbose() << "!!!!!!!!!!!!!!!\n THESE SHOULD BOTH FAIL NOW \n !!!!!!!!!";
        ofAddListener(api.GET_GROUP, this, &ofApp::onGetDeletedGroup);
        api.getGroup( group.id);
        
        ofAddListener(api.GET_EVENT, this, &ofApp::onGetEventFromDeletedGroup);
        api.getEvent( group.id, pieceMakerEventToFail.id );
    }
}
void ofApp::onGetDeletedGroup(GroupEventData& e)
{
    ofLogVerbose() << "SHOULD BE 0 (FAILED) : " << e.groups.size();
}

void ofApp::onGetEventFromDeletedGroup(PiecemakerEventData& e)
{
    ofLogVerbose() << "SHOULD BE 0 (FAILED) : " << e.events.size();
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
