
//
//  oscControll.hpp
//  CSM_Operator
//
//  Created by Florian Born on 22.01.16.
//
//
#pragma once
#include "OscListener.h"
#include "tinyG.hpp"

#define PORT 12000

using namespace ci;
using namespace ci::app;
using namespace std;


class oscControll{
    
    oscControll();
    
private:
    osc::Listener 	listener;
    tinyG &tiny;
public:
    void setup();
    void update();
    float stepSize;
};