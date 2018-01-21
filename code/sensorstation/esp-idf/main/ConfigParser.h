/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConfigParser.h
 * Author: marc
 *
 * Created on 20. Januar 2018, 04:32
 */

#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <string>

class ConfigParser {
public:
    ConfigParser();
    ConfigParser(const ConfigParser& orig);
    virtual ~ConfigParser();
    unsigned int countLines(std::string const& _filename);
private:

};

#endif /* CONFIGPARSER_H */

