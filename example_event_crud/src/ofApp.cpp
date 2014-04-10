#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    numGroupsToCreate = 3;
    login();
}
void ofApp::login()
{
    ofAddListener(api.LOGIN, this, &ofApp::onAPIConnect);
    api.setup("http://piecemaker2-test.herokuapp.com/api/v1");
    // api.login("SuperAdmin", "SuperAdmin");
    api.login("test@fake.motionbank.org", "test@fake.motionbank.org");
}

void ofApp::onAPIConnect(LoginEventData& e)
{
    ofRemoveListener(api.LOGIN, this, &ofApp::onAPIConnect);
    ofLogVerbose() << "apiKey: " << api.apiKey;
    if(e.wasSuccessful())
    {
        createRandomGroups();
    }else
    {
        ofLogError(__func__) << "errorCode: " << e.errorCode << " reason: " << e.errorReason;
    }
    
}

void ofApp::createRandomGroups()
{
    ofAddListener(api.CREATE_GROUP, this, &ofApp::onGroupCreated);
    
    
    for (size_t i=0; i<numGroupsToCreate; i++)
    {
        string title = "title " + ofGetTimestampString();
        string text = "text " + ofGetTimestampString();
        api.createGroup(title, text);
    }
    
}

void ofApp::onGroupCreated(GroupEventData& e)
{
    ofLogVerbose() << "onGroupCreated e.groups.size(): " << e.groups.size();
    //ofRemoveListener(api.CREATE_GROUP, this, &testApp::onGroupCreated);
    for(size_t i =0; i<e.groups.size(); i++)
    {
        groupsToDelete.push_back(e.groups[i]);
    }
    
    if (groupsToDelete.size() == numGroupsToCreate)
    {
        deleteGroups();
    }
}


void ofApp::deleteGroups()
{
    ofAddListener(api.DELETE_GROUP, this, &ofApp::onGroupDeleted);
    for(size_t i =0; i<groupsToDelete.size(); i++)
    {
        Group& group = groupsToDelete[i];
        api.deleteGroup(group.id);
    }
}

void ofApp::onGroupDeleted(GroupEventData& e)
{
    ofLogVerbose() << "onGroupDeleted e.groups.size(): " << e.groups.size();
    for(size_t i =0; i<e.groups.size(); i++)
    {
        for(size_t j =0; j<groupsToDelete.size(); j++)
        {
            if (e.groups[i].id == groupsToDelete[j].id)
            {
                groupsToDelete.erase(groupsToDelete.begin()+j);
            }
        }
    }
    ofLogVerbose() << "groupsToDelete size: " << groupsToDelete.size();
	
	if ( groupsToDelete.size() == 0 )
	{
		ofLogVerbose() << "All groups deleted, done!";
	}
}
//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
