#pragma once

#include "ofMain.h"

#include "ofxHttpUtils.h"
#include "ofxJSONElement.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"

class Group
{
public:
    Group()
    {
        id = -1;
        title = "";
        text = "";
    }
    string print()
    {
        stringstream info;
        info << "id: "                  << id                   << "\n";
        info << "title: "               << title                << "\n";
        info << "text: "               <<  text                << "\n";
        info << "created_at "           << created_at           << "\n";
        info << "created_by_user_id: "  << created_by_user_id   << "\n";
        
        ofLogVerbose(__PRETTY_FUNCTION__) << "\n" << info.str();
        return info.str();
    };
    
    void createFromJSON(Json::Value jsonvalue)
    {
            id = jsonvalue["id"].asInt();
            title = jsonvalue["title"].asString();
            text = jsonvalue["text"].asString();
            created_at = jsonvalue["created_at"].asString();
            created_by_user_id = jsonvalue["created_by_user_id"].asInt();
    };
    int id;
    string title;
    string text;
    string created_at;
    int created_by_user_id;
};

class GroupEventData
{
public:
    GroupEventData()
    {
        
    }
    vector<Group> groups;
    
};

class UserEventData
{
public:
    UserEventData()
    {
        id = -1;
        name = "";
        password = "";
        api_access_key = "";
        is_super_admin = false;
        is_disabled = false;
        
    };
    
    void createFromJSON(Json::Value jsonvalue)
    {
        id = jsonvalue["id"].asInt();
        name = jsonvalue["name"].asString();
        email = jsonvalue["email"].asString();
        password = jsonvalue["password"].asString();
        api_access_key = jsonvalue["api_access_key"].asString();
        is_super_admin = jsonvalue["is_super_admin"].asBool();
        is_disabled = jsonvalue["is_disabled"].asBool();
    };
    string print()
    {
        stringstream info;
        info << "id: "              << id               << "\n";
        info << "name: "            << name             << "\n";
        info << "email "            << email            << "\n";
        info << "password: "        << password         << "\n";
        info << "api_access_key: "  << api_access_key   << "\n";
        info << "is_super_admin: "  << is_super_admin   << "\n";
        info << "is_disabled: "     << is_disabled      << "\n";
        ofLogVerbose(__PRETTY_FUNCTION__) << "\n" << info.str();
        return info.str();
    };

    int id;
    string name;
    string email;
    string password;
    string api_access_key;
    bool is_super_admin;
    bool is_disabled;

};


class EventField
{
public:
    EventField()
    {
        id = "";
        event_id = "";
        value = "";
    };
    
    string event_id;
    string id;
    string value;
    
    void trimEnd(string& inputString)
    {
        inputString.erase(inputString.find_last_not_of(" \n\r\t")+1);
        return inputString;
    };
    
    void createFromJSON(Json::Value jsonvalue)
    {
        id       = ofToString(jsonvalue["id"]);
        event_id = ofToString(jsonvalue["event_id"]);
        value    = ofToString(jsonvalue["value"]);
        trimEnd(id);
        trimEnd(event_id);
        trimEnd(value);
    };
    string print()
    {
        stringstream info;
        info << "id: "              << id           << "\n";
        info << "event_id: "        << event_id     << "\n";
        info << "value: "           << value        << "\n";

       // ofLogVerbose(__PRETTY_FUNCTION__) << "\n" << info.str();
        return info.str();
    };
};


class PiecemakerEvent
{
public:
    PiecemakerEvent()
    {
        id = -1;
        event_group_id = -1;
        created_by_user_id = -1;
        utc_timestamp = -1;
        duration = -1;
        type = "";
        
    }
    void createFromJSON(Json::Value& jsonValue)
    {
        
        Json::Value eventValue = jsonValue["event"];
        Json::Value fieldArray = jsonValue["fields"];
        
        id = eventValue["id"].asInt();
        event_group_id = eventValue["event_group_id"].asInt();
        utc_timestamp = (long)eventValue["utc_timestamp"].asDouble();
        created_by_user_id = eventValue["created_by_user_id"].asInt();
        type = eventValue["type"].asString();
        duration = eventValue["duration"].asDouble();
        
                if(fieldArray.isArray())
        {
            //ofLogVerbose(__func__) << "fields is ARRAY: " << fieldArray.size();
            for(int j= 0; j<fieldArray.size(); j++)
            {
                EventField eventField;
                
                eventField.id       = ofToString(fieldArray[j]["id"]);
                eventField.event_id = ofToString(fieldArray[j]["event_id"]);
                eventField.value    = ofToString(fieldArray[j]["value"]);
                
                eventField.createFromJSON(fieldArray[j]);
                fields.push_back(eventField);
            }
        }
    };
    
    string print()
    {
        stringstream info;
        info << "id: "  << id     << "\n";
        info << "event_group_id: "  << event_group_id     << "\n";
        info << "created_by_user_id: "  << created_by_user_id     << "\n";
        info << "utc_timestamp: "   << utc_timestamp      << "\n";
        info << "duration: "         << duration           << "\n";
        info << "type: "            << type               << "\n";
        info << "fields.size: "     << fields.size()      << "\n";
        for(int j= 0; j<fields.size(); j++)
        {
            info << "field " << j << "\n"  << fields[j].print() << "\n";
        }
        //ofLogVerbose(__PRETTY_FUNCTION__) << "\n" << info.str();
        return info.str();
    };
	int id;
    int event_group_id;
    int created_by_user_id;
	long utc_timestamp;
	float duration;
	string type;
	vector<EventField> fields;

};


class PiecemakerEventData
{
public:
    PiecemakerEventData()
    {
        
    };
    vector<PiecemakerEvent> events;
};

class LoginEventData
{
public:
	LoginEventData()
	{
        errorCode = -1;
        errorReason = "";
		successful = false;
	}
    bool wasSuccessful()
    {
        return successful;
    }
    void setResponse(ofxHttpResponse response_)
    {
        this->response = response_;
        if(response.status <300 && response.status>=200)
        {
            successful = true;
        }else
        {
            errorCode = response.status;
            errorReason = response.reasonForStatus;
            successful = false;
        }
    }
    int errorCode;
    string errorReason;
private:
	ofxHttpResponse response;
    bool successful;
};






class ofxPiecemaker2
{
public:
    ofxPiecemaker2();
    void setup(string url_);
    void login(string userEmail, string userPassword);
    void whoAmI();
    void logout();
    
    void listEvents(int groupId);
    void listEventsOfType(int groupId, string eventType);
    void listEventsWithFields(int groupId, vector<EventField> fields);
    void listEventsBetween(int groupId, long fromUTCTimestamp, long toUTCTimeStamp);
    void findEvents(int groupId, map<string, string> hashMap);
    void getEvent(int groupId, int eventId);
    void createEvent(int groupId, PiecemakerEvent& pieceMakerEvent);
    void deleteEvent(int eventId);
    //TODO Overload?
    //void updateEvent(int groupId, int eventId, HashMap eventData);
    void updateEvent(PiecemakerEvent& pieceMakerEvent);
    
    
    void getUser(int userId);
    void createUser(string userName, string userEmail, string userPassword, string userToken);
    void updateUser(int userId, string userName="", string userEmail="", string userPassword="", string userToken="");
    void listUsers();
    
    void listGroups();
    void getGroup(int groupId);
    void deleteGroup(int groupId);
    void createGroup(string groupTitle = "", string groupText = "");
    //TODO Overload?
    // void updateGroup(int groupId, HashMap groupData);
    void updateGroup(Group& group);
    void getSystemTime();
    string url;
    string apiKey;
    
    ofEvent<UserEventData>  GET_USER;
    ofEvent<UserEventData>  LIST_USERS;
    ofEvent<UserEventData>  CREATE_USER;
    ofEvent<UserEventData>  UPDATE_USER;
    
    
    ofEvent<LoginEventData> LOGIN;
    ofEvent<LoginEventData> LOGOUT;
    
    ofEvent<GroupEventData> GROUP;
    ofEvent<GroupEventData> LIST_GROUPS;
    
    ofEvent<GroupEventData> GET_GROUP;
    ofEvent<GroupEventData> CREATE_GROUP;
    ofEvent<GroupEventData> DELETE_GROUP;
    ofEvent<GroupEventData> UPDATE_GROUP;
    
    ofEvent<PiecemakerEventData> LIST_EVENTS;
    ofEvent<PiecemakerEventData> CREATE_EVENT;
    ofEvent<PiecemakerEventData> DELETE_EVENT;

    ofEvent< Poco::Timestamp> DATE_EVENT;
    
#define OFX_PIECEMAKER_VERSION 2
    static string getVersion() { return ofToString(OFX_PIECEMAKER_VERSION); }
    void printVersion() { ofLogNotice() << getVersion(); }
    
#if 0
    //static string getVersion();
    //void printVersion();
    //void login(string userEmail, string userPassword);
    //void whoAmI();
    //void logout();
    //void getUser(int userId);
    //void listUsers();
    
    //void createUser(string userName, string userEmail, string userPassword, string userToken);
    
    void updateUser(int userId, string userName, string userEmail, string userPassword, string userToken);
    void deleteUser(int userId);
    //void listGroups();
    //void getGroup(int groupId);
    //void createGroup(string groupTitle, string groupText);
    //void updateGroup(int groupId, HashMap groupData);
    //void deleteGroup(int groupId);
    //void listEvents(int groupId);
    //void listEventsOfType(int groupId, string eventType);
    //void listEventsWithFields(Object ... args);
    //void listEventsBetween(int groupId, Date from, Date to);
    //void findEvents(int groupId, HashMap opts);
   // void getEvent(int groupId, int eventId);
    //void createEvent(int groupId, HashMap eventData);
   // void updateEvent(int groupId, int eventId, HashMap eventData);
    //void deleteEvent(int groupId, int eventId);
    //void getSystemTime();
#endif
    
private:
    bool ensureApiKey();
    
    template<typename ListenerMethod>
    ofxHttpUtils* createAPIRequest(ListenerMethod method);
    
    template<typename ListenerMethod>
    void destroyAPIRequest(ofxHttpResponse& response, ListenerMethod method);
    
    string printResponse(ofxHttpResponse response, bool skipBody = false);
    
    
   
    void onLoginResponse(ofxHttpResponse& response);
    void onLogoutResponse(ofxHttpResponse& response);
    void onWhoAmIResponse(ofxHttpResponse& response);
    
    void onGetUserResponse(ofxHttpResponse& response);
    void onListUsersResponse(ofxHttpResponse& response);
    void onCreateUserResponse(ofxHttpResponse& response);
    void onUpdateUserResponse(ofxHttpResponse& response);
    
    void onListGroupsResponse(ofxHttpResponse& response);
    void onGetGroupResponse(ofxHttpResponse& response);
    void onDeleteGroupResponse(ofxHttpResponse& response);
    void onCreateGroupResponse(ofxHttpResponse& response);
    void onUpdateGroupResponse(ofxHttpResponse& response);
    
    void onGetEventResponse(ofxHttpResponse& response);
    void onCreateEventResponse(ofxHttpResponse& response);
    void onDeleteEventResponse(ofxHttpResponse& response);
    void onUpdateEventResponse(ofxHttpResponse& response);
    
    
    void onListEventsResponse(ofxHttpResponse& response);
    void onListEventsWithTypeResponse(ofxHttpResponse& response);
    void onListEventsWithFieldsResponse(ofxHttpResponse& response);
    void onListEventsBetweenResponse(ofxHttpResponse& response);
    void onFindEventsResponse(ofxHttpResponse& response);
    

    
    void onGetSystemTimeResponse(ofxHttpResponse& response);
    
    PiecemakerEventData createEventDataFromResponse(ofxHttpResponse& response);

};