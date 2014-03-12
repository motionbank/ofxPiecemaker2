#include "testApp.h"


void testApp::onListGroups(GroupEventData& e)
{
    ofRemoveListener(api.LIST_GROUP, this, &testApp::onListGroups);
    if (e.groups.empty())
    {
        createGroup();
    }else
    {
        for (size_t i=0; i<e.groups.size(); i++)
        {
            Group& group    = e.groups[i];
            ofLogVerbose() << group.id;
            ofLogVerbose() << group.title;
            ofLogVerbose() << group.text;
            if (group.id == 1)
            {
                // api.addGroupListener(this, &testApp::onGroupOneLoaded);
            }
        }

    }
}
void testApp::onAPIConnect(LoginEventData& e)
{
    ofRemoveListener(api.LOGIN, this, &testApp::onAPIConnect);
    ofLogVerbose(__func__) << "e.response: " << e.response;
    
    ofAddListener(api.LIST_GROUP, this, &testApp::onListGroups);
    api.listGroups();
}

//--------------------------------------------------------------
void testApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofAddListener(api.LOGIN, this, &testApp::onAPIConnect);
    api.connect("http://piecemaker2-test.herokuapp.com", "0310XMMFx35tqryp");
}

void testApp::onListEvents(PiecemakerEventData& e)
{
    ofRemoveListener(api.LIST_EVENTS, this, &testApp::onListEvents);
    if(!e.events.empty())
    {
        for (size_t i=0; i<e.events.size(); i++)
        {
            PiecemakerEvent& event    = e.events[i];
            ofLogVerbose() << "utc_timestamp: "     << event.utc_timestamp;
            ofLogVerbose() << "duration "           << event.duration;
            ofLogVerbose() << "type: "              << event.type;
            ofLogVerbose() << "fields.size: "       << event.fields.size();
        }
    }
    
}

void testApp::onGroupCreated(GroupEventData& e)
{
    ofRemoveListener(api.CREATE_GROUP, this, &testApp::onGroupCreated);
    if (!e.groups.empty())
    {
        ofLogVerbose(__func__) << e.groups[0].title << " CREATED";
        ofAddListener(api.LIST_EVENTS, this, &testApp::onListEvents);
        api.listEvents( e.groups[0].id );
    }
    
}

void testApp::createGroup()
{
    ofAddListener(api.CREATE_GROUP, this, &testApp::onGroupCreated);
    api.createGroup( "Fancy title", "Fancy text");
}


//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}