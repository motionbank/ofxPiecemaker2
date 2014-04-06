#pragma once

#include "ofMain.h"
#include "ofxPiecemaker2.h"



class groupApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
        ofxPiecemaker2 api;
        void onAPIConnect(LoginEventData& e);
    
        void logout();
    
        void onGetSystemTime(Poco::Timestamp& pocoTimestamp);
        void onAPIDisconnect(LoginEventData& e);

        void onListGroups(GroupEventData& e);
        void onGetUser(UserEventData& e);
    
        void listEventsForGroup(int groupId);
        void onListEvents(PiecemakerEventData& e);
        void onGroupCreated(GroupEventData& e);
        void onGroupDeleted(GroupEventData& e);
        void createRandomGroups();
        void deleteAllGroups();
    
		void keyPressed(int key);
		    
    vector<Group> groupsToDelete;
};
