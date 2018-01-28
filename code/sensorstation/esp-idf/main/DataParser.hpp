/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataParser.hpp
 * Author: marc
 *
 * Created on 28. Januar 2018, 09:52
 */

#ifndef DATAPARSER_HPP
#define DATAPARSER_HPP

#include "SPIFFSAccess.h"

class DataParser {
    SPIFFSAccess storage;
    
public:
    DataParser();
    DataParser(const DataParser& orig);
    virtual ~DataParser();
    void storeSensorData(uint8_t _SensorID, double _SensorData, long _SensorDataDate);
    void printSensorData(uint8_t _SensorID);
private:

};

#endif /* DATAPARSER_HPP */

