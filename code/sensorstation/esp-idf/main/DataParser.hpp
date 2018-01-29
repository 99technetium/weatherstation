/* 
 * File:   DataParser.hpp
* Author: Marc Schaefer <marc-schaefer.dev@highdynamics.org>
 *
 * Created on 28. Januar 2018, 09:52
 */

#ifndef DATAPARSER_HPP
#define DATAPARSER_HPP

#include "SPIFFSAccess.h"
#include "SPIFFS.h"
#include "Commands.h"

#include "ArduinoJson.h"

#define SENSOR_DATA_FILE_PREFIX "/SensorData_"

class DataParser {
    SPIFFSAccess storage;
    
public:
    DataParser();
    DataParser(const DataParser& orig);
    virtual ~DataParser();
    void storeSensorData(const char*  _SensorID, double _SensorData, long _SensorDataDate_s, long _SensorDataDate_us);
    void printSensorData(const char*  _SensorID);
    int makeSensorDataJson(const char** _IDs, JsonObject& _Data, DynamicJsonBuffer& _Buffer);
    int cleanAllSensorData();
private:
    String getSensorFileName(const char*  _ID);
};

#endif /* DATAPARSER_HPP */

