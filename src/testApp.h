#pragma once

#include "ofMain.h"
#include "ofxPiecemaker2.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"


class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
        ofxPiecemaker2 api;
        void onAPIConnect(LoginEventData& e);
    
        void logout();
        void getUser(int userID);
    
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
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    vector<Group> groupsToDelete;
};
