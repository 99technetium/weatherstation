/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Prober.hpp
 * Author: marc
 *
 * Created on 27. Januar 2018, 03:46
 */

#ifndef PROBER_HPP
#define PROBER_HPP

#include <string>

#include "DataParser.hpp"

class Prober {
    DataParser parser;
    
public:
    Prober();
    Prober(const Prober& orig);
    virtual ~Prober();
    void sample();
private:
    double measureVBat();
    double measureChannel(uint8_t _Channel);
    double measureLDRonI2C(uint8_t i2cAddress, uint8_t channel);
    double measureTempOnI2C(uint8_t i2cAddress, uint8_t channel);
};

#endif /* PROBER_HPP */

