/* 
 * File:   DataParser.cpp
* Author: Marc Schaefer <marc-schaefer.dev@highdynamics.org>
 * 
 * Created on 28. Januar 2018, 09:52
 */


#include "DataParser.hpp"


DataParser::DataParser() {
    storage.begin();
}

DataParser::DataParser(const DataParser& orig) {
}

DataParser::~DataParser() {
}

void DataParser::storeSensorData(const char* _SensorID, double _SensorData, long _SensorDataDate_s, long _SensorDataDate_us)
{
    String name = getSensorFileName(_SensorID);
    
    StaticJsonBuffer<60> jsonBuffer;
    JsonArray& array = jsonBuffer.createArray();
    array.add(_SensorData);
    array.add(_SensorDataDate_s);
    array.add(_SensorDataDate_us);
    
    String json;
    array.printTo(json);
    json = json +",";
    
    Serial.println(name);
    Serial.println(json);
    
    storage.appendFile(SPIFFS, name.c_str(), json.c_str());
}

void DataParser::printSensorData(const char*  _SensorID)
{
    String name = SENSOR_DATA_FILE_PREFIX;
    String id(_SensorID);
    name = name + id;
    storage.readFile(SPIFFS, name.c_str());
}

String DataParser::getSensorFileName(const char*  _ID)
{
    String name = SENSOR_DATA_FILE_PREFIX;
    String id(_ID);
    return name + id;    
}

//template <std::size_t array_size>
int DataParser::makeSensorDataJson(const char** _IDs, JsonObject& _Data, DynamicJsonBuffer& _Buffer)
{
    String fname;
    String prefix = SENSOR_DATA_FILE_PREFIX;
    String fcontent;
    int i = 0;
    while(_IDs[i] != 0)
    {
        //fname = getSensorFileName(_IDs[i]);
        fname = prefix+String(_IDs[i]);
        Serial.print("READ FROM ID:");
        Serial.println(fname);
        fcontent = storage.readWholeFile(SPIFFS, fname.c_str());
        fcontent = "["+fcontent+"]";
        _Data.set(String(_IDs[i]), _Buffer.parseArray(fcontent));
        i++;
    }
    
    return 1;
}

int DataParser::cleanAllSensorData()
{
    return storage.deleteFileWithPrefix(SENSOR_DATA_FILE_PREFIX);
}