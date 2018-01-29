/* 
 * File:   Connector.cpp
* Author: Marc Schaefer <marc-schaefer.dev@highdynamics.org>
 * 
 * Created on 23. Januar 2018, 18:59
 */

#include "Connector.h"


Connector::Connector() {
}

Connector::Connector(const Connector& orig) {
}

Connector::~Connector() {
}


int Connector::startCommunication()
{
    Serial.print("Connecting to access point ");
    Serial.print(tSSID.c_str());
    
    ArduinoJson::StaticJsonBuffer<200> jsonBuffer;
    
    unsigned long ttl = 0;
    WiFi.begin(tSSID.c_str(), tKey.c_str());    
    while (WiFi.status() != WL_CONNECTED) {
        if(ttl>timeout_connectNetwork_ms ) {
            Serial.println("timeout! Powering down WiFi.");
            Serial.print("Error: ");
            Serial.println(WiFi.status());
            WiFi.disconnect(true);
            return -1;
        }
        delay(500);
        ttl = ttl + 500;        
        Serial.print(".");
    }
    
    Serial.println("connection established!");
    
    Serial.print("Assigned IPv4: ");
    Serial.println(WiFi.localIP());
        
    Serial.print("Connecting to Server ");
    Serial.print(tIP.toString());
    Serial.print(":");
    Serial.println(tPort);
    
    
    if (!client.connect(tIP, tPort)) {
        Serial.println("...failed!");
        return -2;
    } else {
        Serial.println("...connected!");
    }
    
    return 1;
}

int Connector::endCommunication()
{
    Serial.print("Disconnecting from server and network");
    
    client.stop();
    WiFi.disconnect(true);
    
    unsigned long ttl = 0;
    while(client.connected() || WiFi.status() == WL_CONNECTED) 
    {
        if(ttl>timeout_disconnect_ms) {
            if(client.connected()) 
            {
                Serial.println("failed! Still connected to server and network.");
                return -2;
            } else 
            {
                Serial.println("failed! Still connected to the network.");
                return -1;
            }
        }
        Serial.print(".");
        ttl = ttl + 500;
        delay(500);        
    }
    Serial.println("disconnected!");
    return 1;
}

std::string Connector::send(std::string _Data)
{
    Serial.print("Sending...");
    //Serial.println(_Data.c_str());

    client.print(_Data.c_str());
    unsigned long ttl = millis();
    while (client.available() == 0) {
        if (millis() - ttl > timeout_requestServer_ms) {
            Serial.println("timeout! Try again.");
            return NULL;
        }
    }

    String reply = "";
    while(client.available()) {
        reply = reply + client.readString();
    }
    return std::string(reply.c_str());
}

int Connector::setNetwork(String _SSID, String _Key)
{ 
    Serial.print("Set network/key to ");
    Serial.println(_SSID.c_str());
    
    tSSID = _SSID;
    tKey = _Key;
    return 1;
}

int Connector::setServer(IPAddress _IP, uint16_t _Port) 
{
    Serial.print("Set server/port to ");
    Serial.print(_IP.toString());
    Serial.print(":");
    Serial.println(_Port);
    
    tIP = _IP;
    tPort = _Port;
    return 1;
}