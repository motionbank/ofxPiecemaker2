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


class LoginEventData
{
public:
	LoginEventData(string eventName_)
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
    

    ofEvent<LoginEventData> eventDispatcher;
    ofEvent<GroupEventData> groupEventDispatcher;

    
    template<class ListenerClass, typename ListenerMethod>
	void addLoginListener(ListenerClass * listener, ListenerMethod method){
		ofAddListener(eventDispatcher,listener,method);
	}
	template<class ListenerClass, typename ListenerMethod>
	void removeLoginListener(ListenerClass * listener, ListenerMethod method){
		ofRemoveListener(eventDispatcher,listener,method);
	}
    
    template<class ListenerClass, typename ListenerMethod>
	void addGroupListener(ListenerClass * listener, ListenerMethod method){
		ofAddListener(groupEventDispatcher,listener,method);
	}
	template<class ListenerClass, typename ListenerMethod>
	void removeGroupListener(ListenerClass * listener, ListenerMethod method){
		ofRemoveListener(groupEventDispatcher,listener,method);
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
    
};