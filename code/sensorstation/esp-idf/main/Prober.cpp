/* 
 * File:   Prober.cpp
 * Author: Marc Schaefer <marc-schaefer.dev@highdynamics.org>
 * 
 * Created on 27. Januar 2018, 03:46
 */

#include "Prober.hpp"

// R2 = (R1*RL*volt)/(R1*volt+RL*-volt+RL*volt);

Prober::Prober() {
}

Prober::Prober(const Prober& orig) {
}

Prober::~Prober() {
}

void Prober::updateTime(timeval& _Timeval, long& _Time_s, long& _Time_us) 
{
    if(gettimeofday(&_Timeval, NULL) >= 0) 
    {
        _Time_s = _Timeval.tv_sec;
        _Time_us = _Timeval.tv_usec;
    } else {        
        _Time_s = 0;
        _Time_us = 0;
    }    
}

void Prober::sampleToFile()
{
    timeval timer;
    long time_s;
    long time_us;
    updateTime(timer, time_s, time_us);
    parser.storeSensorData(SENSOR_ID_HALL, measureIntHall(), time_s, time_us);
    updateTime(timer, time_s, time_us);
    parser.storeSensorData(SENSOR_ID_VBAT, measureVBat(), time_s, time_us);
    updateTime(timer, time_s, time_us);
    parser.storeSensorData(SENSOR_ID_LDR, measureLDRonI2C(0x48, 0), time_s, time_us);
    updateTime(timer, time_s, time_us);
    parser.storeSensorData(SENSOR_ID_TEMP, measureTempOnI2C(0x48, 1), time_s, time_us);
    /*
    Serial.print("- - - - - -");
    parser.printSensorData(SENSOR_ID_VBAT);
    parser.printSensorData(SENSOR_ID_LDR);
    parser.printSensorData(SENSOR_ID_TEMP);
     */
}

int Prober::getAllSensorData(JsonObject& _Data, DynamicJsonBuffer& _Buffer)
{
    const char* ids[4] = {SENSOR_ID_HALL, SENSOR_ID_VBAT, SENSOR_ID_LDR, SENSOR_ID_TEMP};
    parser.makeSensorDataJson(ids, _Data, _Buffer);    
    return 1;
}

int Prober::cleanAllSensorData()
{
    return parser.cleanAllSensorData();
}


float Prober::measureVBat()
{
    Serial.println("Reading battery voltage...");
    
    analogSetPinAttenuation(GPIO_NUM_2, adc_attenuation_t::ADC_0db);
    uint16_t value = 0;
    value = analogRead(GPIO_NUM_2);
    float mV_batt = 1.79246172980286*value;
    
    String mV_batt_str = String(mV_batt, 2);
    String mV_batt_label = mV_batt_str + " mV";
    Serial.print(mV_batt_label);
    Serial.print(" - ");
    Serial.println(value);    
    
    return mV_batt;
}

float Prober::measureChannel(uint8_t _Channel)
{
    uint16_t value = 0;
    float eff = 0;
    float volt = 0;
    float res = 0;
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

float Prober::measureLDRonI2C(uint8_t i2cAddress, uint8_t channel)
{
    Adafruit_ADS1115 ads(i2cAddress, PIN_I2C_SDA, PIN_I2C_SCL, 100e3);
    ads.begin();
    ads.setGain(GAIN_ONE);
    int16_t value = ads.readADC_SingleEnded(channel);
    float volt = value * 125e-6;
    float res = -(I2C_ADC0_R1*I2C_ADC0_RL*volt)/(I2C_ADC0_R1*volt+I2C_ADC0_RL*-I2C_V+I2C_ADC0_RL*volt);
    float lux = pow(res/LDR1_R100, -1/LDR1_GAMMA)*LDR1_E100;
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

float Prober::measureTempOnI2C(uint8_t i2cAddress, uint8_t channel)
{
    Adafruit_ADS1115 ads(i2cAddress, PIN_I2C_SDA, PIN_I2C_SCL, 100e3);
    ads.begin();
    ads.setGain(GAIN_TWO);
    int16_t value = ads.readADC_SingleEnded(channel);
    float volt = value * 62.5e-6;
    float res = -(I2C_ADC1_R1*I2C_ADC1_RL*volt)/(I2C_ADC1_R1*volt+I2C_ADC1_RL*-I2C_V+I2C_ADC1_RL*volt);
    float temp_K = 1/(NTC1_A1+NTC1_B1*log(res/NTC1_REF)+NTC1_C1*pow(log(res/NTC1_REF),2)+NTC1_D1*pow(log(res/NTC1_REF),3));
    
    
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

float Prober::measureIntHall()
{
        int val = hallRead();
        Serial.print("Hall: ");
        Serial.println(val);
        Serial.println("-----"); 
        return static_cast< float > (val);
}