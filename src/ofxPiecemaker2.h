#pragma once

#include "ofMain.h"

enum CallbackType
{
	GROUP,
	USER,
	LOGIN,
	EVENT
};

class PiecemakerGroup
{
public:
    int id;
    string title;
    string text;
};


class EventData
{
public:
	EventData(string eventName_)
	{
		eventName = eventName_;
	}
	string eventName;
};

class GroupEventData
{
public:
    GroupEventData(vector<PiecemakerGroup> groups_)
    {
        groups = groups_;
    }
    vector<PiecemakerGroup> groups;
    
};



class ofxPiecemaker2
{
public:
    ofxPiecemaker2();
    void setup();
    void connect(string url_, string apiKey_);
    
    
    void listGroups();
    string url;
    string apiKey;
    
    template<class eventType, class ListenerClass, typename ListenerMethod>
	void addListener(eventType type, ListenerClass * listener, ListenerMethod method)
	{
        switch (type)
        {
            case LOGIN:
            {
                ofAddListener(eventDispatcher, listener, method);
                break;
            }
            case GROUP:
            {
                ofAddListener(groupEventDispatcher, listener, method);
                break;
            }
            default:
            {
                ofLogError() << "UNKNOWN TYPE";
            }
        }
		
	}
    template<class ListenerClass, typename ListenerMethod>
	void removeListener(ListenerClass * listener, ListenerMethod method)
	{
		ofRemoveListener(eventDispatcher, listener, method);
	}
    
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
    ofEvent<EventData> eventDispatcher;
    ofEvent<GroupEventData> groupEventDispatcher;
};