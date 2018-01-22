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
#include "WiFi.h"
#include "IPAddress.h"

#include "Communicator.h"

Communicator::Communicator() {
}

Communicator::Communicator(const Communicator& orig) {
}

Communicator::~Communicator() {
}

int Communicator::startCommunication()
{
    Serial.print("Connecting to access point ");
    Serial.print(tSSID.c_str());
    
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

int Communicator::endCommunication()
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

std::string Communicator::send(std::string _Data)
{
    Serial.print("Sending...");
    Serial.println(_Data.c_str());

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

int Communicator::setNetwork(std::string _SSID, std::string _Key)
{ 
    Serial.print("Set network/key to ");
    Serial.println(_SSID.c_str());
    
    tSSID = _SSID;
    tKey = _Key;
    return 1;
}

int Communicator::setServer(IPAddress _IP, uint16_t _Port) 
{
    Serial.print("Set server/port to ");
    Serial.print(_IP.toString());
    Serial.print(":");
    Serial.println(_Port);
    
    tIP = _IP;
    tPort = _Port;
    return 1;
}