/* 
 * File:   Connector.h
* Author: Marc Schaefer <marc-schaefer.dev@highdynamics.org>
 *
 * Created on 23. Januar 2018, 18:59
 */

#ifndef CONNECTOR_H
#define CONNECTOR_H


#include "IPAddress.h"
#include "WiFiClient.h"
#include "WiFi.h"
#include "IPAddress.h"

#include "ArduinoJson.h"

#include <string>

class Connector {
public:
    Connector();
    Connector(const Connector& orig);
    virtual ~Connector();    
    int startCommunication();
    int endCommunication();
    std::string send(std::string _Data);
    int setNetwork(String _SSID, String _Key);
    int setServer(IPAddress _IP, uint16_t _Port);
private:
    String tSSID, tKey;
    IPAddress tIP;
    uint16_t tPort;
    WiFiClient client;
    unsigned long timeout_connectNetwork_ms = 30000;
    unsigned long timeout_requestServer_ms = 5000;
    unsigned long timeout_disconnect_ms = 10000;

};

#endif /* CONNECTOR_H */

