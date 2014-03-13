#include "testApp.h"




#define __func__ __PRETTY_FUNCTION__
//--------------------------------------------------------------
void testApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofAddListener(api.LOGIN, this, &testApp::onAPIConnect);
    api.connect("http://piecemaker2-test.herokuapp.com/api/v1", "0310XMMFx35tqryp");
   // api.login("SuperAdmin", "SuperAdmin");
    api.login("test@fake.motionbank.org", "test@fake.motionbank.org");

}



void testApp::onAPIConnect(LoginEventData& e)
{
    ofRemoveListener(api.LOGIN, this, &testApp::onAPIConnect);
    
    if(e.wasSuccessful())
    {
        ofAddListener(api.LIST_GROUP, this, &testApp::onListGroups);
        api.listGroups();
    }

}

void testApp::onListGroups(GroupEventData& e)
{
    ofRemoveListener(api.LIST_GROUP, this, &testApp::onListGroups);
    if (e.groups.empty())
    {
       // createGroup();
    }else
    {
       /* for (size_t i=0; i<e.groups.size(); i++)
        {
            Group& group    = e.groups[i];
            ofLogVerbose(__func__) << "group.id: " << group.id;
            ofLogVerbose(__func__) << "group.title: " << group.title;
            ofLogVerbose(__func__) << "group.text: " << group.text;
            if (group.id == 1)
            {
                // api.addGroupListener(this, &testApp::onGroupOneLoaded);
            }
        }*/
        
    }
}

void testApp::createGroup()
{
    ofAddListener(api.CREATE_GROUP, this, &testApp::onGroupCreated);
    api.createGroup( "Fancy title", "Fancy text");
}

void testApp::onGroupCreated(GroupEventData& e)
{
    ofRemoveListener(api.CREATE_GROUP, this, &testApp::onGroupCreated);
    if (!e.groups.empty())
    {
        
        for (size_t i=0; i<e.groups.size(); i++)
        {
            ofLogVerbose(__func__) << "e.groups[i].title: " << e.groups[i].title;
            listEventsForGroup(e.groups[i].id);
        }
        
    }
    
}
void testApp::listEventsForGroup(int groupId)
{
    ofLogVerbose(__func__) << "groupId: " << groupId;
    ofAddListener(api.LIST_EVENTS, this, &testApp::onListEvents);
    api.listEvents( groupId );
}

void testApp::onListEvents(PiecemakerEventData& e)
{
    ofRemoveListener(api.LIST_EVENTS, this, &testApp::onListEvents);
    if(!e.events.empty())
    {
        for (size_t i=0; i<e.events.size(); i++)
        {
            PiecemakerEvent& event    = e.events[i];
            ofLogVerbose(__func__) << "event_group_id: "     << event.event_group_id;
            ofLogVerbose(__func__) << "utc_timestamp: "     << event.utc_timestamp;
            ofLogVerbose(__func__) << "duration "           << event.duration;
            ofLogVerbose(__func__) << "type: "              << event.type;
            ofLogVerbose(__func__) << "fields.size: "       << event.fields.size();
        }
    }
    
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