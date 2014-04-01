#include "groupApp.h"


static const char alphanum[] =
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";



char genRandom()
{
    int stringLength = sizeof(alphanum) - 1;
    return alphanum[rand() % stringLength];
};


#define __func__ __PRETTY_FUNCTION__
//--------------------------------------------------------------
void groupApp::setup(){
    
    ofSetLogLevel("ofxHttpUtils", OF_LOG_SILENT);
    ofSetLogLevel("ofAppGLFWWindow", OF_LOG_SILENT);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofAddListener(api.LOGIN, this, &groupApp::onAPIConnect);
    api.setup("http://piecemaker2-test.herokuapp.com/api/v1");
   // api.login("SuperAdmin", "SuperAdmin");
    api.login("test@fake.motionbank.org", "test@fake.motionbank.org");

}



void groupApp::onAPIConnect(LoginEventData& e)
{
    ofRemoveListener(api.LOGIN, this, &groupApp::onAPIConnect);
    ofLogVerbose() << "apiKey: " << api.apiKey;
    if(e.wasSuccessful())
    {
        ofAddListener(api.DATE_EVENT, this, &groupApp::onGetSystemTime);
        api.getSystemTime();
        
    }else
    {
        ofLogError(__func__) << "errorCode: " << e.errorCode << " reason: " << e.errorReason;
    }
    
}

void groupApp::onGetSystemTime(Poco::Timestamp& pocoTimestamp)
{
    ofRemoveListener(api.DATE_EVENT, this, &groupApp::onGetSystemTime);
    Poco::DateTime dateTime(pocoTimestamp);
    
    string timeFormat = "%Y-%m-%d-%H-%M-%S-%i";
    string timestampString = Poco::DateTimeFormatter::format(pocoTimestamp, timeFormat);
    
    ofLogVerbose(__func__) << "timestampString: " << timestampString;
    
    ofAddListener(api.LIST_GROUPS, this, &groupApp::onListGroups);
    api.listGroups();
}

void groupApp::onListGroups(GroupEventData& e)
{
    ofLogVerbose(__func__) << "groups.size(): " << e.groups.size();
    ofRemoveListener(api.LIST_GROUPS, this, &groupApp::onListGroups);
    if (e.groups.empty())
    {
        createRandomGroups();
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

int numGroupsToCreate =2;
void groupApp::createRandomGroups()
{
    ofAddListener(api.CREATE_GROUP, this, &groupApp::onGroupCreated);
    
    for (size_t i=0; i<numGroupsToCreate; i++)
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

void groupApp::onGroupCreated(GroupEventData& e)
{
    ofLogError(__func__) << "groupsToDelete size: " << groupsToDelete.size();

    ofRemoveListener(api.CREATE_GROUP, this, &groupApp::onGroupCreated);
    for (size_t i=0; i<e.groups.size(); i++)
    {
        groupsToDelete.push_back(e.groups[i]);
    }
    if (groupsToDelete.size() == numGroupsToCreate)
    {
        deleteAllGroups();
    }
    
}

void groupApp::onGroupDeleted(GroupEventData& e)
{
    
}


void groupApp::deleteAllGroups()
{
    ofAddListener(api.DELETE_GROUP, this, &groupApp::onGroupDeleted);
    if (!groupsToDelete.empty())
    {
        for (size_t i=0; i<groupsToDelete.size(); i++)
        {
            api.deleteGroup(groupsToDelete[i].id);
        }
        groupsToDelete.clear();
        logout();
    }else
    {
        ofLogError() << "NO GROUPS TO DELETE - RELISTING";
    }
}




void groupApp::logout()
{
    ofAddListener(api.LOGOUT, this, &groupApp::onAPIDisconnect);
    api.logout();
}

void groupApp::onAPIDisconnect(LoginEventData& e)
{
    ofRemoveListener(api.LOGIN, this, &groupApp::onAPIDisconnect);
    
    if(e.wasSuccessful())
    {
        ofLogVerbose() << "LOGOUT PASS";
    }else
    {
        ofLogError(__func__) << "errorCode: " << e.errorCode << " reason: " << e.errorReason;
    }
    
}


void groupApp::listEventsForGroup(int groupId)
{
    ofLogVerbose(__func__) << "groupId: " << groupId;
    ofAddListener(api.LIST_EVENTS, this, &groupApp::onListEvents);
    api.listEvents( groupId );
}

void groupApp::onListEvents(PiecemakerEventData& e)
{
    ofLogVerbose(__func__) << "events.size(): " << e.events.size();
    ofRemoveListener(api.LIST_EVENTS, this, &groupApp::onListEvents);
    if(!e.events.empty())
    {
        for (size_t i=0; i<e.events.size(); i++)
        {
            PiecemakerEvent& event    = e.events[i];
            event.print();
        }
    }
    
}



//--------------------------------------------------------------
void groupApp::update(){

}

//--------------------------------------------------------------
void groupApp::draw(){

}

//--------------------------------------------------------------
void groupApp::keyPressed(int key)
{
    if (key == 'D')
    {
       
    }
    if (key == 'x')
    {
        logout();
        
    }
}
