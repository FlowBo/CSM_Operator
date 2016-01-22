#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "tinyG.hpp"
#include "cinder/Rand.h"
#include "OscListener.h"

using namespace ci;
using namespace ci::app;
using namespace std;


#define PORT 12000

class CSM_OperatorApp : public App {
public:
    void setup() override;
    void mouseDown( MouseEvent event ) override;
    void update() override;
    void draw() override;
    void keyDown(KeyEvent event) override;
    osc::Listener 	listener;
    tinyG           tiny;
    int moveXPlus = 0;
    float stepSize = 1;
    bool feedhold = false;
};

void CSM_OperatorApp::setup()
{
    tiny.setup();
//    tiny.sendGcode("$ej 1");
    tiny.sendGcode("g91");
    listener.setup( PORT );
    console() << "OSC Listen to: " << PORT << endl;
    string s = "/move/x";
    console() << s.find("move") << endl;
    s = "/value/step";
    console() << "No move" <<s.find("move") << endl;
}

void CSM_OperatorApp::mouseDown( MouseEvent event )
{
}

void CSM_OperatorApp::update()
{
    
    while( listener.hasWaitingMessages() ) {
        osc::Message message;
        listener.getNextMessage( &message );
        
        
//        console() << "New message received" << std::endl;
        console() << "Address: " << message.getAddress() << std::endl;
        console() << "Num Arg: " << message.getNumArgs() << std::endl;
//

        string oscMessage = message.getAddress();
        if (oscMessage.find("move") == 1) {
            stepSize = message.getArgAsFloat(0);
            ostringstream ss;
            ss << stepSize;
            console() << oscMessage << "__" << ss.str() << endl;
            if(oscMessage == "/move/x")
            {
                tiny.sendGcode("g0x"+ss.str());
            }else if (oscMessage == "/move/y"){
                tiny.sendGcode("g0y"+ss.str());
            }
            else if (oscMessage == "/move/z"){
                tiny.sendGcode("g0z"+ss.str());
            }
            else if (oscMessage == "/move/a"){
                tiny.sendGcode("g0a"+ss.str());
            }
            
        }else if(oscMessage == "/control/hold") {
            feedhold = !feedhold;
            console() << "found feedhold" << endl;
            if (feedhold) {
                tiny.sendGcode("!");
            }else{
                tiny.sendGcode("~");
            }
        }
        else{
            console() << "found unimplemented Code: " << endl;
            console() << message.getAddress() << endl;
        }
    }
    tiny.update();
}

void CSM_OperatorApp::draw()
{
    gl::clear( Color( 0, 0, 0 ) );
    
}



void CSM_OperatorApp::keyDown(KeyEvent event){
    if (event.getChar() == ' ') {
        ostringstream ss;
        ss << ci::Rand::randFloat(0, 50);
        tiny.sendGcode("g0x"+ss.str());
        //        console() << "g0x" + randValue.str() << endl;
        
        
    }
}

CINDER_APP( CSM_OperatorApp, RendererGl )
