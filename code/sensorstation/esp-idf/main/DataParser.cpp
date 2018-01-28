/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataParser.cpp
 * Author: marc
 * 
 * Created on 28. Januar 2018, 09:52
 */

#include "SPIFFS.h"
#include "ArduinoJson.h"

#include "DataParser.hpp"

#define SENSOR_DATA_FILE_PREFIX "/SensorData_"

DataParser::DataParser() {
    storage.begin();
}

DataParser::DataParser(const DataParser& orig) {
}

DataParser::~DataParser() {
}

void DataParser::storeSensorData(uint8_t _SensorID, double _SensorData, long _SensorDataDate)
{
    String name = SENSOR_DATA_FILE_PREFIX;
    String id(_SensorID);
    
    StaticJsonBuffer<60> jsonBuffer;
    JsonArray& array = jsonBuffer.createArray();
    array.add(_SensorData);
    array.add(_SensorDataDate);
    
    String json;
    array.printTo(json);
    json = json +",";
    
    name = name + id;
    
    Serial.println(name);
    Serial.println(json);
    
    storage.appendFile(SPIFFS, name.c_str(), json.c_str());
}

void DataParser::printSensorData(uint8_t _SensorID)
{
    String name = SENSOR_DATA_FILE_PREFIX;
    String id(_SensorID);
    name = name + id;
    storage.readFile(SPIFFS, name.c_str());
}