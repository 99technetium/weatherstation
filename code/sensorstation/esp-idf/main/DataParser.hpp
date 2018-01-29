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

#include "ArduinoJson.h"

#define SENSOR_DATA_FILE_PREFIX "/SensorData_"

class DataParser {
    SPIFFSAccess storage;
    
public:
    DataParser();
    DataParser(const DataParser& orig);
    virtual ~DataParser();
    void storeSensorData(uint8_t _SensorID, double _SensorData, long _SensorDataDate_s, long _SensorDataDate_us);
    void printSensorData(uint8_t _SensorID);
    //template <std::size_t array_size>
    int makeSensorDataJson(uint8_t (&_IDs)[4], JsonObject& _Data, DynamicJsonBuffer& _Buffer);
private:
    String getSensorFileName(uint8_t _ID);
};

#endif /* DATAPARSER_HPP */

