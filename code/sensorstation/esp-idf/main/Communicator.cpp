/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Communicator.cpp
 * Author: marc
 * 
 * Created on 22. Januar 2018, 03:48
 */

#include "Communicator.h"

#include "Commander.h"
#include "ArduinoJson.h"

Communicator::Communicator(Commander& _Origin) 
{
    cmdr = &_Origin;
}

Communicator::Communicator(const Communicator& orig) 
{
}

Communicator::~Communicator() 
{
}

int Communicator::start(std::string _SSID, std::string _Key, IPAddress _IP, uint16_t _Port)
{   
    con.setNetwork(_SSID, _Key);
    con.setServer(_IP, _Port);    
    return con.startCommunication();   
}

int Communicator::end()
{
    return con.endCommunication();
}

ArduinoJson::JsonObject& Communicator::sendSensorData(Commander& _Origin, ArduinoJson::JsonObject _Data)
{
    StaticJsonBuffer<200> jsonBuffer;
    return jsonBuffer.parseObject("");
}

ArduinoJson::JsonObject& Communicator::requestUpdate(Commander& _Origin, ArduinoJson::JsonObject _Config)
{
    StaticJsonBuffer<200> jsonBuffer;
    return jsonBuffer.parseObject("");
}