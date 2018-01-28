/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Prober.cpp
 * Author: marc
 * 
 * Created on 27. Januar 2018, 03:46
 */

#include "Prober.hpp"

#include <math.h>
#include "Arduino.h"
#include "Pinmap.hpp"
#include "Adafruit_ADS1015.h"

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

#define SENSOR_ID_VBAT  0
#define SENSOR_ID_LDR   1
#define SENSOR_ID_TEMP  2

// R2 = (R1*RL*volt)/(R1*volt+RL*-volt+RL*volt);

Prober::Prober() {
}

Prober::Prober(const Prober& orig) {
}

Prober::~Prober() {
}

void Prober::sample()
{
    parser.storeSensorData(SENSOR_ID_VBAT, measureVBat(), 100003);
    parser.storeSensorData(SENSOR_ID_LDR, measureLDRonI2C(0x48, 0), 100004);
    parser.storeSensorData(SENSOR_ID_TEMP, measureTempOnI2C(0x48, 1), 100005);
    Serial.print("- - - - - -");
    parser.printSensorData(SENSOR_ID_VBAT);
    parser.printSensorData(SENSOR_ID_LDR);
    parser.printSensorData(SENSOR_ID_TEMP);
}


double Prober::measureVBat()
{
    Serial.println("Reading battery voltage...");
    
    analogSetPinAttenuation(GPIO_NUM_2, adc_attenuation_t::ADC_0db);
    uint16_t value = 0;
    value = analogRead(GPIO_NUM_2);
    double mV_batt = 1.79246172980286*value;
    
    String mV_batt_str = String(mV_batt, 2);
    String mV_batt_label = mV_batt_str + " mV";
    Serial.print(mV_batt_label);
    Serial.print(" - ");
    Serial.println(value);    
    
    return mV_batt;
}

double Prober::measureChannel(uint8_t _Channel)
{
    uint16_t value = 0;
    double eff = 0;
    double volt = 0;
    double res = 0;
    switch(_Channel)
    {
        case PIN_ADC_1:
                analogSetPinAttenuation(GPIO_NUM_2, adc_attenuation_t::ADC_0db);   
                value = analogRead(GPIO_NUM_2);
                volt = value*0.0002685546875;
                res = -(ADC1_R1*ADC1_RL*volt)/(ADC1_R1*volt+ADC1_RL*-ADC_V+ADC1_RL*volt);
                eff = 1/(NTC1_A1+NTC1_B1*log(res/NTC1_REF)+NTC1_C1*pow(log(res/NTC1_REF),2)+NTC1_D1*pow(log(res/NTC1_REF),3));
                Serial.print("Value: ");
                Serial.println(value);
                Serial.print("Volt: ");
                Serial.println(volt, 3);
                Serial.print("Resistance: ");
                Serial.println(res, 10);
                Serial.print("Temp: ");
                Serial.println(eff, 10);
    Serial.println("------");
            break;
    }
    return eff;
}

double Prober::measureLDRonI2C(uint8_t i2cAddress, uint8_t channel)
{
    Adafruit_ADS1115 ads(i2cAddress, PIN_I2C_SDA, PIN_I2C_SCL, 100e3);
    ads.begin();
    ads.setGain(GAIN_ONE);
    int16_t value = ads.readADC_SingleEnded(channel);
    double volt = value * 125e-6;
    double res = -(I2C_ADC0_R1*I2C_ADC0_RL*volt)/(I2C_ADC0_R1*volt+I2C_ADC0_RL*-I2C_V+I2C_ADC0_RL*volt);
    double lux = pow(res/LDR1_R100, -1/LDR1_GAMMA)*LDR1_E100;
    /*
    Serial.print("I2C Value: ");
    Serial.println(value);
    Serial.print("I2C Volt: ");
    Serial.println(volt,6);
    Serial.print("I2C Resistance: ");
    Serial.println(res,8);
    */
    Serial.print("I2C: ");
    Serial.print(lux,8);
    Serial.println(" Lux");
    Serial.println("------");
    return lux;
}

double Prober::measureTempOnI2C(uint8_t i2cAddress, uint8_t channel)
{
    Adafruit_ADS1115 ads(i2cAddress, PIN_I2C_SDA, PIN_I2C_SCL, 100e3);
    ads.begin();
    ads.setGain(GAIN_TWO);
    int16_t value = ads.readADC_SingleEnded(channel);
    double volt = value * 62.5e-6;
    double res = -(I2C_ADC1_R1*I2C_ADC1_RL*volt)/(I2C_ADC1_R1*volt+I2C_ADC1_RL*-I2C_V+I2C_ADC1_RL*volt);
    double temp_K = 1/(NTC1_A1+NTC1_B1*log(res/NTC1_REF)+NTC1_C1*pow(log(res/NTC1_REF),2)+NTC1_D1*pow(log(res/NTC1_REF),3));
    
    
    Serial.print("Value: ");
    Serial.println(value);
    Serial.print("Volt: ");
    Serial.println(volt, 3);
    Serial.print("Resistance: ");
    Serial.println(res, 10);
    
    Serial.print("I2C: ");
    Serial.print(temp_K, 6);
    Serial.print(" K - ");
    Serial.print(temp_K - 273.15, 6);
    Serial.println(" °C");
    Serial.println("------");
    return temp_K;
}