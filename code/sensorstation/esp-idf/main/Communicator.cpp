/* 
 * File:   Communicator.cpp
* Author: Marc Schaefer <marc-schaefer.dev@highdynamics.org>
 * 
 * Created on 22. Januar 2018, 03:48
 */

#include "Communicator.h"

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

int Communicator::start(String _SSID, String _Key, IPAddress _IP, uint16_t _Port)
{   
    con.setNetwork(_SSID, _Key);
    //con.setServer(_IP, _Port);    
    return con.startCommunication();   
}

int Communicator::startFromConfig()
{
        Preferences preferences;
        preferences.begin("config", false);
        
        if(preferences.getBool(PREF_KEY_INIT, false))
        { 
            IPAddress ip;
            ip.fromString(preferences.getString(PREF_KEY_SRV_IP));
            return start(preferences.getString(PREF_KEY_SSID), preferences.getString(PREF_KEY_WIFIKEY), ip, preferences.getUShort(PREF_KEY_SRV_PORT));
        } else {
            return -1;
        }    
}

int Communicator::end()
{
    return con.endCommunication();
}

ArduinoJson::JsonObject& Communicator::sendSensorData(Commander& _Origin, ArduinoJson::JsonObject& _Data, ArduinoJson::DynamicJsonBuffer& _Buffer)
{
    JsonObject& actionObj = _Buffer.createObject();
    actionObj.set(CMD_ACTION_ID_DATA_ADD_SENSORDATA, _Data);
    JsonObject& cmdObj = _Buffer.createObject();
    cmdObj.set(CMD_ID_DATA, actionObj);
    
    String data;
    cmdObj.printTo(data);
    std::string reply;
    std::string data_str(data.c_str());
    reply = con.send(data_str);
    StaticJsonBuffer<200> jsonBuffer;
    
    return jsonBuffer.parseObject(reply.c_str());
}

ArduinoJson::JsonObject& Communicator::requestUpdate(Commander& _Origin, ArduinoJson::JsonObject& _Config)
{
    StaticJsonBuffer<200> jsonBuffer;
    return jsonBuffer.parseObject("");
}