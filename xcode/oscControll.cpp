//
//  oscControll.cpp
//  CSM_Operator
//
//  Created by Florian Born on 22.01.16.
//
//

#include "oscControll.hpp"


oscControll::oscControll(){};

void oscControll::setup(){
    listener.setup(PORT);
    console() << "OSC is listening to PORT: "  << PORT << endl;
}

void oscControll::update(){
    while( listener.hasWaitingMessages() ) {
        osc::Message message;
        listener.getNextMessage( &message );
        console() << "Address: " << message.getAddress() << std::endl;
        console() << "Num Arg: " << message.getNumArgs() << std::endl;
        string oscMessage = message.getAddress();
        if (oscMessage.find("move") == 1) {
            ostringstream ss;
            stepSize = message.getArgAsFloat(0);
            ss << stepSize;
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

}