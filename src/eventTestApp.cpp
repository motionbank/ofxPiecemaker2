#include "eventTestApp.h"




int TEST_GROUP_ID = 109;

#define __func__ __PRETTY_FUNCTION__
//--------------------------------------------------------------
void eventTestApp::setup(){
    
    ofSetLogLevel("ofxHttpUtils", OF_LOG_SILENT);
    ofSetLogLevel("ofAppGLFWWindow", OF_LOG_SILENT);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofAddListener(api.LOGIN, this, &eventTestApp::onAPIConnect);
    api.setup("http://piecemaker2-test.herokuapp.com/api/v1");
    api.login("test@fake.motionbank.org", "test@fake.motionbank.org");

}



void eventTestApp::onAPIConnect(LoginEventData& e)
{
    ofRemoveListener(api.LOGIN, this, &eventTestApp::onAPIConnect);
    ofLogVerbose() << "apiKey: " << api.apiKey;
    if(e.wasSuccessful())
    {
        ofAddListener(api.GET_GROUP, this, &eventTestApp::onGetGroup);
        api.getGroup(TEST_GROUP_ID);
    }else
    {
        ofLogError(__func__) << "errorCode: " << e.errorCode << " reason: " << e.errorReason;
    }
    
}

void eventTestApp::onGetGroup(GroupEventData& e)
{
    
    ofRemoveListener(api.GET_GROUP, this, &eventTestApp::onGetGroup);
    if (e.groups.empty())
    {
        ofLogError(__func__) << "NO GROUPS";
    }else
    {
        ofLogVerbose(__func__) << "groups.size(): " << e.groups.size();
        for (size_t i=0; i<e.groups.size(); i++)
        {
            Group& group    = e.groups[i];
            group.print();
            listEventsForGroup(group.id);
            
        }
    }
}





void eventTestApp::listEventsForGroup(int groupId)
{
    ofLogVerbose(__func__) << "groupId: " << groupId;
    ofAddListener(api.LIST_EVENTS, this, &eventTestApp::onListEvents);
    //api.listEvents( groupId );
    api.listEventsOfType( groupId, "video" );
    
}

void eventTestApp::onListEvents(PiecemakerEventData& e)
{
    ofLogVerbose(__func__) << "events.size(): " << e.events.size();
    ofRemoveListener(api.LIST_EVENTS, this, &eventTestApp::onListEvents);
    if(!e.events.empty())
    {
        for (size_t i=0; i<e.events.size(); i++)
        {
            PiecemakerEvent& event    = e.events[i];
            //ofLogVerbose(__func__) << event.print();
        }
    }
    
}

//--------------------------------------------------------------
void eventTestApp::update(){

}

//--------------------------------------------------------------
void eventTestApp::draw(){

}

//--------------------------------------------------------------
void eventTestApp::keyPressed(int key){
   
    if (key == 'x')
    {
        
    }
  
}

