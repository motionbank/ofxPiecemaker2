//
//  ofxPiecemaker2.cpp
//  PieceMaker2Api
//
//  Created by jason van cleave on 3/10/14.
//
//

//#define __func__ __PRETTY_FUNCTION__

#include "ofxPiecemaker2.h"
#include "Poco/DateTimeFormatter.h"



ofxPiecemaker2::ofxPiecemaker2()
{
    apiKey = "";
    url = "";
}

void ofxPiecemaker2::setup(string url_)
{
    this->url = url_;
}

void ofxPiecemaker2::onLoginResponse(ofxHttpResponse& response)
{
    printResponse(response);
    destroyAPIRequest(response, &ofxPiecemaker2::onLoginResponse);
    
    ofxJSONElement parser;
    parser.parse(ofToString(response.responseBody));
    
    this->apiKey = parser["api_access_key"].asString();
    
    LoginEventData eventData;
    eventData.setResponse(response);
    ofNotifyEvent(LOGIN, eventData);
}

void ofxPiecemaker2::login(string userEmail, string userPassword)
{
    ofxHttpUtils* httpUtils = createAPIRequest(&ofxPiecemaker2::onLoginResponse);
    
    ofxHttpForm form;
	form.action = url + "/user/login";
	form.method = OFX_HTTP_POST;
    form.addFormField( "token",    apiKey );
    form.addFormField( "email",    userEmail );
    form.addFormField( "password", userPassword );
    
	httpUtils->addForm(form);
    

}
void ofxPiecemaker2::onLogoutResponse(ofxHttpResponse& response)
{
    destroyAPIRequest(response, &ofxPiecemaker2::onLogoutResponse);
    LoginEventData eventData;
    eventData.setResponse(response);
    ofNotifyEvent(LOGOUT, eventData);
}

void ofxPiecemaker2::logout()
{
    ofxHttpUtils* httpUtils = createAPIRequest(&ofxPiecemaker2::onLogoutResponse);

    ofxHttpForm form;
	form.action = url + "/user/logout";
	form.method = OFX_HTTP_POST;
    
    httpUtils->addForm(form);
}

void ofxPiecemaker2::onWhoAmIResponse(ofxHttpResponse& response)
{
    
    destroyAPIRequest(response, &ofxPiecemaker2::onWhoAmIResponse);

    
}
void ofxPiecemaker2::whoAmI()
{
    ofxHttpUtils* httpUtils = createAPIRequest(&ofxPiecemaker2::onWhoAmIResponse);
    
    ofxHttpForm form;
	form.action = url + "/user/me";
	form.method = OFX_HTTP_GET;
    
	httpUtils->addForm(form);
}

#pragma mark USER METHODS


void ofxPiecemaker2::onListUsersResponse(ofxHttpResponse& response)
{
    
    destroyAPIRequest(response, &ofxPiecemaker2::onListUsersResponse);
}

void ofxPiecemaker2::listUsers()
{
    ofxHttpUtils* httpUtils = createAPIRequest(&ofxPiecemaker2::onListUsersResponse);

    ofxHttpForm form;
	form.action = url + "/users";
	form.method = OFX_HTTP_GET;
    
	httpUtils->addForm(form);
}

void ofxPiecemaker2::onGetUserResponse(ofxHttpResponse& response)
{
  
    
    destroyAPIRequest(response, &ofxPiecemaker2::onGetUserResponse);
    
    ofxJSONElement parser;
    parser.parse(ofToString(response.responseBody));
    UserEventData eventData;
    eventData.createFromJSON(parser);
    ofLogVerbose(__func__) << eventData.print();
    ofNotifyEvent(GET_USER, eventData);
}

void ofxPiecemaker2::getUser(int userId)
{
    ofxHttpUtils* httpUtils = createAPIRequest(&ofxPiecemaker2::onGetUserResponse);

    ofxHttpForm form;
	form.action = url + "/user/" + ofToString(userId);
	form.method = OFX_HTTP_GET;
    
	httpUtils->addForm(form);
}

#pragma mark EVENT METHODS
void ofxPiecemaker2::onGetEventResponse(ofxHttpResponse& response)
{
    destroyAPIRequest(response, &ofxPiecemaker2::onGetEventResponse);
}

void ofxPiecemaker2::getEvent(int groupId, int eventId)
{
    ofxHttpUtils* httpUtils = createAPIRequest(&ofxPiecemaker2::onGetEventResponse);
    ofxHttpForm form;
	form.action = url + "/group/" + ofToString(groupId) + "/event/" + ofToString(eventId);
	form.method = OFX_HTTP_GET;
    
	httpUtils->addForm(form);
}

PiecemakerEventData ofxPiecemaker2::createEventDataFromResponse(ofxHttpResponse& response)
{
    ofxJSONElement parser;
    parser.parse(ofToString(response.responseBody));
    
    PiecemakerEventData eventData;
    vector<PiecemakerEvent> events;
    if(parser.isArray())
    {
        ofLogVerbose(__func__) << "parser isArray(): " << parser.isArray() << " size " << parser.size();
        for(int i= 0; i<parser.size(); i++)
        {
            PiecemakerEvent event;
            event.createFromJSON(parser[i]);
            events.push_back(event);
        }
    }else
    {
        if (parser.isObject())
        {
            ofLogVerbose(__func__) << "isObject()!";
        }
    }
    
    eventData.events = events;
    return eventData;

}
void ofxPiecemaker2::onListEventsResponse(ofxHttpResponse& response)
{
    destroyAPIRequest(response, &ofxPiecemaker2::onListEventsResponse);
    
    if (response.reasonForStatus != "OK")
    {
        ofLogError(__func__) << "WEIRD RESPONSE: " << response.reasonForStatus;
        
        ofLogVerbose(__func__) << printResponse(response, true);
        return;
    }
    
    PiecemakerEventData eventData = createEventDataFromResponse(response);
    ofNotifyEvent(LIST_EVENTS, eventData);
    
}


void ofxPiecemaker2::listEvents(int groupId)
{
    ofxHttpUtils* httpUtils = createAPIRequest(&ofxPiecemaker2::onListEventsResponse);
    ofxHttpForm form;
	form.action = url + "/group/" + ofToString(groupId) + "/events";
	form.method = OFX_HTTP_GET;
    
	httpUtils->addForm(form);
   
}

void ofxPiecemaker2::onListEventsWithTypeResponse(ofxHttpResponse& response)
{
    destroyAPIRequest(response, &ofxPiecemaker2::onListEventsWithTypeResponse);
    
    if (response.reasonForStatus != "OK")
    {
        ofLogError(__func__) << "WEIRD RESPONSE: " << response.reasonForStatus;
        
        ofLogVerbose(__func__) << printResponse(response, true);
        return;
    }
    
    PiecemakerEventData eventData = createEventDataFromResponse(response);
    ofNotifyEvent(LIST_EVENTS, eventData);
    
}
void ofxPiecemaker2::listEventsOfType(int groupId, string eventType)
{
    ofxHttpUtils* httpUtils = createAPIRequest(&ofxPiecemaker2::onListEventsWithTypeResponse);
    ofxHttpForm form;
	form.action = url + "/group/" + ofToString(groupId) + "/events";
    form.addFormField( "type", eventType );
	form.method = OFX_HTTP_GET;
    
	httpUtils->addForm(form);
    
}

void ofxPiecemaker2::onFindEventsResponse(ofxHttpResponse& response)
{
     destroyAPIRequest(response, &ofxPiecemaker2::onFindEventsResponse);
    if (response.reasonForStatus != "OK")
    {
        ofLogError(__func__) << "WEIRD RESPONSE: " << response.reasonForStatus;
        
        ofLogVerbose(__func__) << printResponse(response, true);
        return;
    }
    PiecemakerEventData eventData = createEventDataFromResponse(response);
    ofNotifyEvent(LIST_EVENTS, eventData);
}

void ofxPiecemaker2::findEvents(int groupId, map<string, string> hashMap)
{
    ofxHttpUtils* httpUtils = createAPIRequest(&ofxPiecemaker2::onFindEventsResponse);
    ofxHttpForm form;
	form.action = url + "/group/" + ofToString(groupId) + "/events";
    typename map<string, string>::iterator it = hashMap.begin();
    while (it != hashMap.end())
    {
        form.addFormField( (*it).first, (*it).second );
        ++it;
    }
    
	form.method = OFX_HTTP_GET;
    
	httpUtils->addForm(form);

}

void ofxPiecemaker2::onListEventsWithFieldsResponse(ofxHttpResponse& response)
{
    destroyAPIRequest(response, &ofxPiecemaker2::onListEventsWithFieldsResponse);
    if (response.reasonForStatus != "OK")
    {
        ofLogError(__func__) << "WEIRD RESPONSE: " << response.reasonForStatus;
        
        ofLogVerbose(__func__) << printResponse(response, true);
        return;
    }
    PiecemakerEventData eventData = createEventDataFromResponse(response);
    ofNotifyEvent(LIST_EVENTS, eventData);
}

void ofxPiecemaker2::listEventsWithFields(int groupId, vector<EventField>fields)
{
    
    
    ofxHttpUtils* httpUtils = createAPIRequest(&ofxPiecemaker2::onListEventsWithFieldsResponse);
    ofxHttpForm form;
	form.action = url + "/group/" + ofToString(groupId) + "/events";
    
    for(size_t i=0; i< fields.size(); i++)
    {
        EventField field = fields[i];
       
        
        if (!field.id.empty())
        {
            Json::Value idValue;
            idValue["id"] = field.id;
            
            form.addFormField( "fields[id]", ofToString(idValue) );
        }
        if (!field.event_id.empty())
        {
            //fieldsValue["event_id"] = field.event_id;
           // form.addFormField( "field[event_id]", field.event_id );
        }
        
        if (!field.value.empty())
        {
            Json::Value aValue;
            aValue["value"] = field.value;
            ofLogVerbose(__func__) << "aValue: " << aValue;
            form.addFormField( "fields", ofToString(aValue) );
            //fieldsValue["value"] = field.value;
            //form.addFormField( "field[value]", field.value );
        }
        //ofLogVerbose() << "fieldsValue: " << ofToString(fieldsValue);
        //form.addFormField( "fields", "[" + ofToString(fieldsValue) + "]");
    }
	form.method = OFX_HTTP_GET;
    
	httpUtils->addForm(form);
}

void ofxPiecemaker2::onCreateEventResponse(ofxHttpResponse& response)
{
    destroyAPIRequest(response, &ofxPiecemaker2::onCreateEventResponse);
    PiecemakerEventData eventData; //TODO Generic response type needed?
    ofNotifyEvent(CREATE_EVENT, eventData);
}

void ofxPiecemaker2::createEvent(int groupId, PiecemakerEvent& pieceMakerEvent)
{
    ofLogVerbose(__func__) << "groupId: " << groupId << " "  << pieceMakerEvent.print();
    ofxHttpUtils* httpUtils = createAPIRequest(&ofxPiecemaker2::onCreateEventResponse);
    ofxHttpForm form;
	form.action = url + "/group/" + ofToString(groupId) + "/event";
    form.addFormField( "duration", ofToString(pieceMakerEvent.duration) ); //TODO timestamp bad
    form.addFormField( "type", pieceMakerEvent.type );
    form.addFormField( "utc_timestamp", ofToString(pieceMakerEvent.utc_timestamp) );
    
    for(int i=0; i<pieceMakerEvent.fields.size(); i++)
    {
        EventField& field = pieceMakerEvent.fields[i];
        
        string formFieldKey = "fields["+field.id+"]";
        
        form.addFormField( formFieldKey, field.value );
    }
    
	form.method = OFX_HTTP_POST;
    
	httpUtils->addForm(form);
}


#pragma mark GROUP METHODS
void ofxPiecemaker2::onCreateGroupResponse(ofxHttpResponse& response)
{
    destroyAPIRequest(response, &ofxPiecemaker2::onCreateGroupResponse);
    vector<Group> groups;
    GroupEventData eventData;
    eventData.groups = groups;
    ofNotifyEvent(CREATE_GROUP, eventData);
}

void ofxPiecemaker2::createGroup(string title, string text)
{
    ofxHttpUtils* httpUtils = createAPIRequest(&ofxPiecemaker2::onCreateGroupResponse);
    ofxHttpForm form;
	form.action = url + "/group";
    form.addFormField( "title", title );
    form.addFormField( "text", text );
	form.method = OFX_HTTP_POST;
    
	httpUtils->addForm(form);
    
}
void ofxPiecemaker2::onDeleteGroupResponse(ofxHttpResponse& response)
{
   
    destroyAPIRequest(response, &ofxPiecemaker2::onDeleteGroupResponse);
    ofxJSONElement parser;
    parser.parse(ofToString(response.responseBody));
    
    GroupEventData eventData;
    ofNotifyEvent(GET_GROUP, eventData);
    
}

void ofxPiecemaker2::onGetGroupResponse(ofxHttpResponse& response)
{
    
    destroyAPIRequest(response, &ofxPiecemaker2::onGetGroupResponse);
    ofxJSONElement parser;
    parser.parse(ofToString(response.responseBody));
    
    vector<Group> groups;

    if(parser.isArray())
    {
        ofLogVerbose(__func__) << "MULTIPLE ELEMENTS: " << parser.size();
        
        for(int i= 0; i<parser.size(); i++)
        {
            Group group;
            group.createFromJSON(parser[i]);
            groups.push_back(group);
        }
        
    }else
    {
        Group singleGroup;
        singleGroup.createFromJSON(parser);
        groups.push_back(singleGroup);
        ofLogVerbose(__func__) << "SINGLE ELEMENT: " << singleGroup.print();
        
    }
    GroupEventData eventData;
    eventData.groups = groups;
    ofNotifyEvent(GET_GROUP, eventData);
}

void ofxPiecemaker2::deleteGroup(int groupId)
{
    ofLogVerbose(__func__) << "REQUEST TO DELETE groupId:" << groupId;
    
    ofxHttpUtils* httpUtils = createAPIRequest(&ofxPiecemaker2::onDeleteGroupResponse);
    ofxHttpForm form;
	form.action = url + "/group/" + ofToString(groupId);
	form.method = OFX_HTTP_DELETE;

	httpUtils->addForm(form);

}
void ofxPiecemaker2::getGroup(int groupId)
{
    //ofLogVerbose(__func__) << "groupId: " << groupId;
    ofxHttpUtils* httpUtils = createAPIRequest(&ofxPiecemaker2::onGetGroupResponse);
    ofxHttpForm form;
	form.action = url + "/group/" + ofToString(groupId);
	form.method = OFX_HTTP_GET;
    
	httpUtils->addForm(form);
}

void ofxPiecemaker2::listGroups()
{
    
    ofxHttpUtils* httpUtils = createAPIRequest(&ofxPiecemaker2::onListGroupsResponse);
    ofxHttpForm form;
	form.action = url + "/groups";
	form.method = OFX_HTTP_GET;
	httpUtils->addForm(form);
    
    //ofLogVerbose(__func__) << "form.action: " << form.action;
    
}

void ofxPiecemaker2::onListGroupsResponse(ofxHttpResponse& response)
{
    destroyAPIRequest(response, &ofxPiecemaker2::onListGroupsResponse);
    
    vector<Group> groups;
    
    ofxJSONElement parser;
    parser.parse(ofToString(response.responseBody));
    
    if(parser.isArray())
    {
        //ofLogVerbose(__func__) << "MULTIPLE ELEMENTS: " << parser.size();
        
        for(int i= 0; i<parser.size(); i++)
        {
            Group group;
            group.createFromJSON(parser[i]);
            groups.push_back(group);
        }
        
    }
    
    GroupEventData eventData;
    eventData.groups = groups;
    ofNotifyEvent(LIST_GROUPS, eventData);

}

void ofxPiecemaker2::onGetSystemTimeResponse(ofxHttpResponse& response)
{
    destroyAPIRequest(response, &ofxPiecemaker2::onGetSystemTimeResponse);
    
    ofLogVerbose(__func__) << printResponse(response); // responseBody: {"utc_timestamp":1395683209.9653654}

    ofxJSONElement parser;
    parser.parse(ofToString(response.responseBody));
    
    //parser["utc_timestamp"].asString();
    
    ofLogVerbose(__func__) << "utc_timestamp: " << parser["utc_timestamp"];
   // Int64 value = parser["utc_timestamp"].asInt64();
    
    
    //ofLogVerbose(__func__) << "value: " << value;
    
    Poco::Timestamp pocoTimestamp;
    pocoTimestamp.fromUtcTime(parser["utc_timestamp"].asDouble());
   
    //responseString << "timestamp: " << timestampString << "\n";
    
     ofNotifyEvent(DATE_EVENT, pocoTimestamp);
}

void ofxPiecemaker2::getSystemTime()
{
    ofxHttpUtils* httpUtils = createAPIRequest(&ofxPiecemaker2::onGetSystemTimeResponse);
    ofxHttpForm form;
	form.action = url + "/system/utc_timestamp";
	form.method = OFX_HTTP_GET;
	httpUtils->addForm(form);
}

#pragma mark PRIVATE METHODS

template<typename ListenerMethod>
ofxHttpUtils* ofxPiecemaker2::createAPIRequest(ListenerMethod method)
{
    ofxHttpUtils* httpUtils = new ofxHttpUtils();
    ofAddListener(httpUtils->newResponseEvent, this, method);
    httpUtils->start();
    httpUtils->customHeaders["X-Access-Key"] = apiKey;
    return httpUtils;
}

template<typename ListenerMethod>
void ofxPiecemaker2::destroyAPIRequest(ofxHttpResponse& response, ListenerMethod method)
{
    if(!response.httpUtils)
    {
        ofLogError() << "response.httpUtils WAS NULL!";
        return;
    }
    response.httpUtils->stop();
    ofRemoveListener(response.httpUtils->newResponseEvent, this, method);
    //ofLogVerbose(__func__) << printResponse(response);
    delete response.httpUtils;
    response.httpUtils = NULL;
}

string ofxPiecemaker2::printResponse(ofxHttpResponse response, bool skipBody)
{
    stringstream responseString;
    responseString << "status: "            << response.status          << "\n";
    responseString << "reasonForStatus: "   << response.reasonForStatus << "\n";
    responseString<< "contentType: "        << response.contentType     << "\n";
    if(!skipBody)
    {
        responseString << "responseBody: "      << response.responseBody    << "\n";
    }
    
    
    string timeFormat = "%Y-%m-%d-%H-%M-%S-%i";
    string timestampString = Poco::DateTimeFormatter::format(response.timestamp, timeFormat);
    responseString << "timestamp: " << timestampString << "\n";
    
    return responseString.str();
}

bool ofxPiecemaker2::ensureApiKey()
{
    if (!apiKey.empty())
    {
        
        return true;
    }
    //ofLogError() << "API Key is empty:" << apiKey;
    return false;
}