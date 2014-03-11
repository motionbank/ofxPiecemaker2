#include "testApp.h"


void testApp::onListGroups(PiecemakerEventData& eventData)
{
    api.removeListener(this, &testApp::onListGroups);
    
}
void testApp::onAPIConnect(PiecemakerEventData& eventData)
{
    api.removeListener(LOGIN, this, &testApp::onAPIConnect);
    ofLogVerbose(__func__) << "eventName: " << eventData.eventName;
    api.addListener(GROUP, this, &testApp::onListGroups);
    api.listGroups();
}

//--------------------------------------------------------------
void testApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    api.addListener(LOGIN, this, &testApp::onAPIConnect);
    api.connect("http://piecemaker2-test.herokuapp.com", "0310XMMFx35tqryp");
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}