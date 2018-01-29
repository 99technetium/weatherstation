/* 
 * File:   Communicator.h
* Author: Marc Schaefer <marc-schaefer.dev@highdynamics.org>
 *
 * Created on 22. Januar 2018, 03:48
 */

#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "Commander.h"
#include "Connector.h"

#include "ArduinoJson.h"

#include <Preferences.h>


class Commander;

class Communicator {
public:
    Communicator(Commander& _Origin);
    Communicator(const Communicator& orig);
    virtual ~Communicator();
    int start(String _SSID, String _Key, IPAddress _IP, uint16_t _Port);
    int startFromConfig();
    int end();
    ArduinoJson::JsonObject& sendSensorData(Commander& _Origin, ArduinoJson::JsonObject& _Data, ArduinoJson::DynamicJsonBuffer& _Buffer);
    ArduinoJson::JsonObject& requestUpdate(Commander& _Origin, ArduinoJson::JsonObject& _Config);
private:
    Connector con;    
    Commander* cmdr;
};

#endif /* COMMUNICATOR_H */

