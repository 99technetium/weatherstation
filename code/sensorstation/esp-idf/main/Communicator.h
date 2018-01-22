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

#include <string>
#include "IPAddress.h"
#include "WiFiClient.h"

class Communicator {
public:
    Communicator();
    Communicator(const Communicator& orig);
    virtual ~Communicator();
    int startCommunication();
    int endCommunication();
    std::string send(std::string _Data);
    int setNetwork(std::string _SSID, std::string _Key);
    int setServer(IPAddress _IP, uint16_t _Port);
private:
    std::string tSSID, tKey;
    IPAddress tIP;
    uint16_t tPort;
    WiFiClient client;
    unsigned long timeout_connectNetwork_ms = 30000;
    unsigned long timeout_requestServer_ms = 5000;
    unsigned long timeout_disconnect_ms = 10000;
    
    
};

#endif /* COMMUNICATOR_H */

