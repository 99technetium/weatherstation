/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Communicator.h
 * Author: marc
 *
 * Created on 22. Januar 2018, 03:48
 */

#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "Connector.h"
#include "Commander.h"
#include "ArduinoJson.h"



class Communicator {
public:
    Communicator(Commander& _Origin);
    Communicator(const Communicator& orig);
    virtual ~Communicator();
    int start(std::string _SSID, std::string _Key, IPAddress _IP, uint16_t _Port);
    int end();
    ArduinoJson::JsonObject& sendSensorData(Commander& _Origin, ArduinoJson::JsonObject _Data);
    ArduinoJson::JsonObject& requestUpdate(Commander& _Origin, ArduinoJson::JsonObject _Config);
private:
    Connector con;    
    Commander* cmdr;
};

#endif /* COMMUNICATOR_H */

