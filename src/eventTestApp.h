#pragma once

#include "ofMain.h"
#include "ofxPiecemaker2.h"


class eventTestApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
        ofxPiecemaker2 api;
        void onAPIConnect(LoginEventData& e);
    
        void onGetGroup(GroupEventData& e);
    
        void listEventsForGroup(int groupId);
        void onListEvents(PiecemakerEventData& e);
        void onCreateEvent(PiecemakerEventData& e);
        void onDeleteEvent(PiecemakerEventData& e);
        void createRandomEvent();
    
		void keyPressed(int key);

        vector<PiecemakerEvent> eventsToDelete;
        void deleteListedEvents();
        
};
