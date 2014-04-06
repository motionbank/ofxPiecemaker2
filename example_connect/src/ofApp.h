#pragma once

#include "ofMain.h"
#include "ofxPiecemaker2.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    
    ofxPiecemaker2 api;
    void onAPIConnect(LoginEventData& e);
    
    void onListGroups(GroupEventData& e);
    void createRandomGroups();
    void onGroupCreated(GroupEventData& e);
    void listEventsForGroup(int groupId);
    void onListEvents(PiecemakerEventData& e);
    
    void login();
    void logout();
    void onAPIDisconnect(LoginEventData& e);
    bool isConnected;
    
};
