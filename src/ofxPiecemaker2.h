#pragma once

#include "ofMain.h"

class Group
{
public:
    int id;
    string title;
    string text;
};

class PiecemakerEvent
{
public:
    PiecemakerEvent()
    {
        id = -1;
        utc_timestamp = "";
        duration = 0;
        type = "";
        
    }
	int id;
	string utc_timestamp;
	long duration;
	string type;
	map<int, string> fields;

};

class LoginEventData
{
public:
	LoginEventData()
	{
		response = "";
	}
	string response;
};

class GroupEventData
{
public:
    GroupEventData(vector<Group> groups_)
    {
        groups = groups_;
    }
    vector<Group> groups;
    
};

class PiecemakerEventData
{
public:
    PiecemakerEventData();
    vector<PiecemakerEvent> events;
};


class ofxPiecemaker2
{
public:
    ofxPiecemaker2();
    void setup();
    void connect(string url_, string apiKey_);
    
    
    void listEvents(int groupId);
    
    
    void listGroups();
    void createGroup(string groupTitle = "", string groupText = "");
    string url;
    string apiKey;
    

    ofEvent<LoginEventData> LOGIN;
    ofEvent<GroupEventData> GROUP;
    ofEvent<GroupEventData> LIST_GROUP;
    ofEvent<GroupEventData> CREATE_GROUP;
    ofEvent<PiecemakerEventData> LIST_EVENTS;
    
#if 0
    static string getVersion();
    void printVersion();
    void login(string userEmail, string userPassword);
    void logout();
    void listUsers();
    void whoAmI();
    void createUser(string userName, string userEmail, string userPassword, string userToken);
    void getUser(int userId);
    void updateUser(int userId, string userName, string userEmail, string userPassword, string userToken);
    void deleteUser(int userId);
    void listGroups();
    void getGroup(int groupId);
    void createGroup(string groupTitle, string groupText);
    void updateGroup(int groupId, HashMap groupData);
    void deleteGroup(int groupId);
    void listEvents(int groupId);
    void listEventsOfType(int groupId, string eventType);
    void listEventsWithFields(Object ... args);
    void listEventsBetween(int groupId, Date from, Date to);
    void findEvents(int groupId, HashMap opts);
    void getEvent(int groupId, int eventId);
    void createEvent(int groupId, HashMap eventData);
    void updateEvent(int groupId, int eventId, HashMap eventData);
    void deleteEvent(int groupId, int eventId);
    void getSystemTime();
#endif
    
private:
    bool ensureApiKey();
    
};