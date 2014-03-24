#include "ofMain.h"


#define use_testApp
//#define use_eventTestApp

#ifdef use_testApp

#include "testApp.h"
//========================================================================
int main( ){

	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}

#endif


#ifdef use_eventTestApp

#include "eventTestApp.h"
//========================================================================
int main( ){
    
	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new eventTestApp());
    
}

#endif