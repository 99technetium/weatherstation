/* 
 * File:   Prober.hpp
 * Author: Marc Schaefer <marc-schaefer.dev@highdynamics.org>
 *
 * Created on 27. Januar 2018, 03:46
 */

#ifndef PROBER_HPP
#define PROBER_HPP


#include "DataParser.hpp"
#include "Pinmap.hpp"

#include "Arduino.h"
#include "ArduinoJson.h"

#include "Adafruit_ADS1015.h"

#include <math.h>
#include <string>
#include <sys/time.h>

#define ADC_V       3.3
#define I2C_V       3.3

#define NTC1_A1     3.354016e-3
#define NTC1_B1     2.569850e-4
#define NTC1_C1     2.62013E-12
#define NTC1_D1     6.38309E-15
#define NTC1_REF    10e3

#define LDR1_GAMMA 0.75
#define LDR1_R100 20e3
#define LDR1_E100 100

#define ADC1_R1     4700    
#define ADC1_RL     2400

#define I2C_ADC0_R1 10e3
#define I2C_ADC0_RL 6e6

#define I2C_ADC1_R1 10e3
#define I2C_ADC1_RL 6e6


class Prober {
    DataParser parser;
    
    const char* SENSOR_ID_HALL="HALL";
    const char* SENSOR_ID_VBAT="VBAT";
    const char* SENSOR_ID_LDR="LDR";
    const char* SENSOR_ID_TEMP="TEMP";
public: 
    Prober();
    Prober(const Prober& orig);
    virtual ~Prober();
    void sampleToFile(uint16_t _Samples);
    int getAllSensorData(JsonObject& _Data, DynamicJsonBuffer& _Buffer);
    int cleanAllSensorData();
private:
    void updateTime(timeval& _Timeval, long& _Time_s, long& _Time_us);
    
    float measureVBat();
    float measureChannel(uint8_t _Channel);
    float measureLDRonI2C(uint8_t i2cAddress, uint8_t channel);
    float measureTempOnI2C(uint8_t i2cAddress, uint8_t channel);
    float measureIntHall();
};

#endif /* PROBER_HPP */

