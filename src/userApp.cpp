#include "userApp.h"




#define __func__ __PRETTY_FUNCTION__
//--------------------------------------------------------------
void userApp::setup(){
    
    ofSetLogLevel("ofxHttpUtils", OF_LOG_SILENT);
    ofSetLogLevel("ofAppGLFWWindow", OF_LOG_SILENT);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofAddListener(api.LOGIN, this, &userApp::onAPIConnect);
    api.setup("http://piecemaker2-test.herokuapp.com/api/v1");
    //api.login("SuperAdmin", "SuperAdmin");
    //api.login("test@fake.motionbank.org", "test@fake.motionbank.org");
    api.login("jvcleave@gmail.com", "MRRdjI");
    
}



void userApp::onAPIConnect(LoginEventData& e)
{
    ofRemoveListener(api.LOGIN, this, &userApp::onAPIConnect);
    ofLogVerbose() << "apiKey: " << api.apiKey;
    if(e.wasSuccessful())
    {
    
        //do something usery
        getUser(1);
    }else
    {
        ofLogError(__func__) << "errorCode: " << e.errorCode << " reason: " << e.errorReason;
    }
    
}


void userApp::onGetUser(UserEventData& e)
{
     ofRemoveListener(api.GET_USER, this, &userApp::onGetUser);
    ofLogVerbose(__PRETTY_FUNCTION__) << "";
    e.print();
}


void userApp::getUser(int userID)
{
    ofAddListener(api.GET_USER, this, &userApp::onGetUser);
    api.getUser(userID);
}

void userApp::onCreateUser(UserEventData& e)
{

}
void userApp::createUser()
{
    
    ofAddListener(api.CREATE_USER, this, &userApp::onCreateUser);
    api.createUser("Mr "+ofGetTimestampString(), ofGetTimestampString()+"@horses.org", ofGetTimestampString(), ofGetTimestampString());
}

//--------------------------------------------------------------
void userApp::update(){

}

//--------------------------------------------------------------
void userApp::draw(){

}

//--------------------------------------------------------------
void userApp::keyPressed(int key){
    if (key == 'u')
    {
        getUser(3);
        
    }
    if (key == 'c')
    {
        createUser();
        
    }
}