/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Connector.h
 * Author: marc
 *
 * Created on 23. Januar 2018, 18:59
 */

#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <string>
#include "IPAddress.h"
#include "WiFiClient.h"

class Connector {
public:
    Connector();
    Connector(const Connector& orig);
    virtual ~Connector();    
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

#endif /* CONNECTOR_H */

