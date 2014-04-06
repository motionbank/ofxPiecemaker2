#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
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
        ofAddListener(api.CREATE_GROUP, this, &ofApp::onGroupCreated);
        string title = "Test group from OF";
        string text = "Test text from OF";
        api.createGroup(title, text);
    }else
    {
        ofLogError(__func__) << "errorCode: " << e.errorCode << " reason: " << e.errorReason;
    }
    
}
void ofApp::onGroupCreated(GroupEventData& e)
{
    ofLogVerbose() << "onGroupCreated";
    ofRemoveListener(api.CREATE_GROUP, this, &ofApp::onGroupCreated);
    if (e.groups.empty())
    {
        ofLogError() << "NO GROUPS RETURNED";
    }else
    {
        myGroups  = e.groups;
        ofLogVerbose() << "myGroups size: " << myGroups.size();
        ofAddListener(api.CREATE_EVENT, this, &ofApp::onCreateEvent);
        PiecemakerEvent pieceMakerEvent;
        Poco::Timestamp now;
        //now.update();
        pieceMakerEvent.utc_timestamp = (long)now.utcTime();
        pieceMakerEvent.type = "test-type-OF";
        pieceMakerEvent.duration = 3000;
        EventField field;
        field.id = "test of field id";
        field.value = "test of field value";
        pieceMakerEvent.fields.push_back(field);

        ofLogVerbose() << "e.groups[0]: \n" << e.groups[0].print();
        
        api.createEvent(e.groups[0].id, pieceMakerEvent);
    }
    
}

void ofApp::onCreateEvent(PiecemakerEventData& e)
{
    ofLogVerbose(__func__) << "PiecemakerEventData.events size " << e.events.size();
    ofRemoveListener(api.CREATE_EVENT, this, &ofApp::onCreateEvent);
    
    //now find it
    ofAddListener(api.LIST_EVENTS, this, &ofApp::onListEvents);
    
    for(int i= 0; i<e.events.size(); i++)
    {
        PiecemakerEvent& event = e.events[i];
        ofLogVerbose() << event.print();
        ofLogVerbose(__func__) << "event.fields.size: " << event.fields.size();
        api.listEventsWithFields(event.event_group_id, event.fields);
    }
    
}
void ofApp::onListEvents(PiecemakerEventData& e)
{
    ofLogVerbose(__func__) << "events.size()-------------------------------->: " << e.events.size();
    ofRemoveListener(api.LIST_EVENTS, this, &ofApp::onListEvents);
    if(!e.events.empty())
    {
        for (size_t i=0; i<e.events.size(); i++)
        {
            PiecemakerEvent& event    = e.events[i];
            ofLogVerbose(__func__) << event.print();
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
