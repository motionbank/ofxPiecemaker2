#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetLogLevel("ofxHttpUtils", OF_LOG_SILENT);
    
    ofAddListener(api.LOGIN, this, &ofApp::onAPIConnect);
    api.setup("http://piecemaker2-test.herokuapp.com/api/v1");
    api.login("SuperAdmin", "SuperAdmin");

}

void ofApp::onAPIConnect(LoginEventData& e)
{
    ofRemoveListener(api.LOGIN, this, &ofApp::onAPIConnect);
    ofLogVerbose() << "apiKey: " << api.apiKey;
    if(e.wasSuccessful())
    {
        ofAddListener(api.LIST_USERS, this, &ofApp::onListUsers);
        api.listUsers();
    }else
    {
        ofLogError(__func__) << "errorCode: " << e.errorCode << " reason: " << e.errorReason;
    }
    
}
int numUsersToUpdate = 0;
int numUsersUpdated = 0;
void ofApp::onListUsers(UserEventData& e)
{
    ofRemoveListener(api.LIST_USERS, this, &ofApp::onListUsers);
    ofAddListener(api.UPDATE_USER, this, &ofApp::onUserUpdated);
    if(e.users.empty())
    {
        ofLogError() << "NO USERS";
    }else
    {
        vector<User> usersToUpdate;
        for (size_t i=0; i<e.users.size(); i++)
        {
            User& user = e.users[i];
            
            if(ofIsStringInString(user.name, "test") || ofIsStringInString(user.name, "fake"))
            {
                numUsersToUpdate++;
                ofLogVerbose() << user.print();
                if (user.name == "fake")
                {
                    user.name = "test";
                }else
                {
                    if (user.name == "test")
                    {
                        user.name = "fake";
                    }
                }
                usersToUpdate.push_back(user);
               
            }
        }
        numUsersToUpdate = usersToUpdate.size();
        for (size_t i=0; i<usersToUpdate.size(); i++)
        {
            api.updateUser(usersToUpdate[i]);
        }
        
    }
}

void ofApp::onUserUpdated(UserEventData& e)
{
    
    ofLogVerbose() << "numUsersUpdated: " << numUsersUpdated << " e.users.size: " << e.users.size();
    if(e.users.empty())
    {
        ofLogError() << "NO USERS";
    }else
    {
        User& user = e.users[0];
        ofLogVerbose() << user.print();
        if (user.id == 6)
        {
            ofAddListener(api.DELETE_USER, this, &ofApp::onUserDeleted);
            api.deleteUser(user.id);
        }
    }
    
    numUsersUpdated++;
    if (numUsersUpdated >= numUsersToUpdate)
    {
        ofLogVerbose() << "COMPLETE";
        numUsersUpdated = 0;
        numUsersToUpdate = 0;
    }
}

void ofApp::onUserDeleted(UserEventData& e)
{
    ofLogVerbose(__func__) << " e.users.size: " << e.users.size();
    if(e.users.empty())
    {
        ofLogError(__func__) << "NO USERS";
    }else
    {
        User& user = e.users[0];
        ofLogVerbose(__func__) << user.print();
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
