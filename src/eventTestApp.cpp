#include "eventTestApp.h"




int TEST_GROUP_ID = 109;

#define __func__ __PRETTY_FUNCTION__
//--------------------------------------------------------------
void eventTestApp::setup(){
    
    //ofSetLogLevel("ofxHttpUtils", OF_LOG_SILENT);
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

    int testId = 5;
    
    ofLogVerbose(__func__) << "groupId: " << groupId;
    ofAddListener(api.LIST_EVENTS, this, &eventTestApp::onListEvents);
    switch (testId)
    {
        case 0: //List All Events
        {
            api.listEvents( groupId );
            break;
        }
        case 1: //Find Events
        {
            map<string,string> hashMap;
            hashMap["type"] = "scenefaux";
            api.findEvents(groupId, hashMap);
            break;
        }
        case 2: //List All Events
        {
            vector<EventField> fields;
            EventField f1;
            f1.id = "created_by";
            f1.value  = "Allison";
            //fields.push_back(f1);
            
            EventField f2;
            f2.id = "type";
            f2.value  = "marker";
            //fields.push_back(f2);
            
            EventField f4;
            f4.id = "location";
            f4.value  = "LAB Halle Frankfurt";
            fields.push_back(f4);
            
            api.listEventsWithFields(groupId, fields);
            break;
        }
        case 4: //List Events of type
        {
            api.listEventsOfType( groupId, "marker" );
            break;
        }
        case 5: //List Events of type
        {
            //Wed, 20 Apr 2011 19:30:37 GMT
            //Thu, 21 Apr 2011 09:23:57 GMT
            //219 responses
            api.listEventsBetween( groupId, 1303327837, 1303377837 );
            break;
        }
        default:
        {
            ofRemoveListener(api.LIST_EVENTS, this, &eventTestApp::onListEvents);
             break;
        }
           
    }
}

void eventTestApp::onListEvents(PiecemakerEventData& e)
{
    ofLogVerbose(__func__) << "events.size()-------------------------------->: " << e.events.size();
    ofRemoveListener(api.LIST_EVENTS, this, &eventTestApp::onListEvents);
    if(!e.events.empty())
    {
        eventsToDelete = e.events;
        for (size_t i=0; i<e.events.size(); i++)
        {
            PiecemakerEvent& event    = e.events[i];
            ofLogVerbose(__func__) << event.print();
        }
    }
    
}

void eventTestApp::onCreateEvent(PiecemakerEventData& e)
{
    ofLogVerbose(__func__) << "";
    ofRemoveListener(api.CREATE_EVENT, this, &eventTestApp::onCreateEvent);
}
void eventTestApp::createRandomEvent()
{
    ofAddListener(api.CREATE_EVENT, this, &eventTestApp::onCreateEvent);
    PiecemakerEvent pieceMakerEvent;
    Poco::Timestamp now;
    now.update();
    pieceMakerEvent.utc_timestamp = (long)now.utcTime();
    ofLogVerbose() << "pieceMakerEvent.utc_timestamp: " << pieceMakerEvent.utc_timestamp << " now.utcTime(): " << now.utcTime();
    pieceMakerEvent.type = "test-type-OF";
    pieceMakerEvent.duration = 3000;
    
    for (int i = 0; i<4; i++)
    {
        EventField field;
        field.id = "test.of.field.id" + ofToString(i);
        field.value = "test.of.field.value"+ ofToString(i);
        pieceMakerEvent.fields.push_back(field);
    }
   
    
    api.createEvent(TEST_GROUP_ID, pieceMakerEvent);
}

void eventTestApp::onDeleteEvent(PiecemakerEventData& e)
{
    ofLogVerbose(__func__) << "";
    ofRemoveListener(api.DELETE_EVENT, this, &eventTestApp::onCreateEvent);
}

void eventTestApp::deleteListedEvents()
{
    for (size_t i=0; i<eventsToDelete.size(); i++)
    {
        PiecemakerEvent& event    = eventsToDelete[i];
        if (i%2 == 0)
        {
            ofAddListener(api.DELETE_EVENT, this, &eventTestApp::onDeleteEvent);
            api.deleteEvent(event.id);
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
   
    if (key == 'c')
    {
        //createRandomEvent();
    }
    if (key == 'x')
    {
        //deleteListedEvents();
    }
}

