#pragma once

#include "ofMain.h"
#include "ofxPiecemaker2.h"



class userApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
        ofxPiecemaker2 api;
        void onAPIConnect(LoginEventData& e);
    
        void logout();
        void getUser(int userID);
        void createUser();

        void onGetUser(UserEventData& e);
        void onCreateUser(UserEventData& e);
		void keyPressed(int key);

};
