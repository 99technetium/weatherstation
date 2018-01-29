/* 
 * File:   ConfigParser.h
* Author: Marc Schaefer <marc-schaefer.dev@highdynamics.org>
 *
 * Created on 20. Januar 2018, 04:32
 */

#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"
#include "esp_err.h"
#include "esp_spiffs.h"

#include "Arduino.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>

class ConfigParser {
public:
    ConfigParser();
    ConfigParser(const ConfigParser& orig);
    virtual ~ConfigParser();
    unsigned int countLines(std::string const& _filename);
private:

};

#endif /* CONFIGPARSER_H */

