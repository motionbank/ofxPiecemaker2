#include "testApp.h"


void testApp::onListGroups(GroupEventData& eventData)
{
    api.removeGroupListener(this, &testApp::onListGroups);
    
    for (size_t i=0; i<eventData.groups.size(); i++)
    {
        PiecemakerGroup& group = eventData.groups[i];
        ofLogVerbose() << group.id;
        ofLogVerbose() << group.title;
        ofLogVerbose() << group.text;
        if (group.id == 1)
        {
           // api.addGroupListener(this, &testApp::onGroupOneLoaded);
        }
    }
    
}
void testApp::onAPIConnect(LoginEventData& eventData)
{
    api.removeLoginListener(this, &testApp::onAPIConnect);
    ofLogVerbose(__func__) << "eventName: " << eventData.eventName;
    api.addGroupListener(this, &testApp::onListGroups);
    api.listGroups();
}

//--------------------------------------------------------------
void testApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    api.addLoginListener(this, &testApp::onAPIConnect);
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