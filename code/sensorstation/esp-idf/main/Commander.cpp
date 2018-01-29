/* 
 * File:   Commander.cpp
 * Author: Marc Schaefer <marc-schaefer.dev@highdynamics.org>
 * 
 * Created on 23. Januar 2018, 23:08
 */

#include "Commander.h"

RTC_DATA_ATTR bool      init_cfg = 0;

RTC_DATA_ATTR uint64_t  sleep_time_us = 0;
RTC_DATA_ATTR uint64_t  sleep_time_ref = 0;
RTC_DATA_ATTR uint64_t  sleep_time_too_short = 0;
RTC_DATA_ATTR uint64_t  sleep_time_target = 0;

RTC_DATA_ATTR uint16_t  sample_cycles = 1;

RTC_DATA_ATTR uint16_t  actual_sample_cycle = 0;

using namespace std;

Commander::Commander()
{
    nvs_flash_init();
    tcpip_adapter_init();
    //ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
    initArduino();
    
    Serial.begin(115200);
    delay(10);
    
    init();
    initConfig();
    ++actual_sample_cycle;
    sleep_time_target = 10*1e6;  // in us
    
    // Sampling
    Prober prober;
    
    powerPeripheral(true);
    prober.sampleToFile();
    delay(300);
    powerPeripheral(false);    
    
    // Send data
    if(actual_sample_cycle >= sample_cycles)
    {    
        DynamicJsonBuffer jsonBuffer;
        JsonObject& data = jsonBuffer.createObject();
        prober.getAllSensorData(data, jsonBuffer);
        
        Communicator com(*this);
        com.startFromConfig();
        com.sendSensorData(*this, data);
        
        actual_sample_cycle = 0;
    }
    
    sleep();
    
    /*
    while(1)
    {        
        int val = hallRead();
        Serial.print("Hall: ");
        Serial.println(val);
        Serial.println("-----");
    }
    std::string ssid     = "cu";
    std::string password = "C9zwhLPm";
    
    uint16_t port = 8080;
    IPAddress ip(10, 42, 0, 1);
    
    Communicator com(*this);
    com.start(ssid, password, ip, port);
    com.end();
    */
}

Commander::Commander(const Commander& orig) 
{
}

Commander::~Commander() 
{
}

int Commander::setConfig(unsigned int _CMD_ID, void* _Args) 
{
    return 0;
}

void Commander::init()
{
    pinMode(PIN_RELAY_PPWR_CTRL1, OUTPUT);
    pinMode(PIN_RELAY_PPWR_CTRL2, OUTPUT);
    pinMode(PIN_RELAY_AUX_CTRL1, OUTPUT);
    pinMode(PIN_RELAY_AUX_CTRL2, OUTPUT);
            
    digitalWrite(PIN_RELAY_PPWR_CTRL1, LOW);
    digitalWrite(PIN_RELAY_PPWR_CTRL2, LOW);
    digitalWrite(PIN_RELAY_AUX_CTRL1, LOW);
    digitalWrite(PIN_RELAY_AUX_CTRL2, LOW);    
}

void Commander::initConfig()
{
    if(!init_cfg)
    {
        Preferences preferences;
        preferences.begin("config", false);
        
        if(!preferences.getBool(PREF_KEY_INIT, false))
        {        
            preferences.putString(PREF_KEY_SSID, "Apartment_EG_2.4GHz_new");
            preferences.putString(PREF_KEY_WIFIKEY, "5455922329870587");

            IPAddress ip(192, 168, 5, 154);
            preferences.putString(PREF_KEY_SRV_IP, ip.toString());
            preferences.putUShort(PREF_KEY_SRV_PORT, 8080);

            preferences.putUShort(PREF_KEY_SLEEPTIME, 0);
            preferences.putUShort(PREF_KEY_NUMBER_CYCLES, 0);
            preferences.putUShort(PREF_KEY_NUMBER_SAMPLES, 1);
            
            preferences.putBool(PREF_KEY_INIT, true);
        }
        
        sleep_time_target = preferences.getUShort(PREF_KEY_SLEEPTIME, 0);
        sleep_time_us = sleep_time_target*FACTOR_MIN_TO_US;
        
        actual_sample_cycle = preferences.getUShort(PREF_KEY_NUMBER_CYCLES, 0);
                
        init_cfg = true;
        preferences.end();
    }    
}

// TODO: Check for overflow
void Commander::sleep() 
{
    timeval timer;
    
    if(gettimeofday(&timer, NULL) >= 0) 
    {                
        uint64_t timestamp = timer.tv_sec*1e6+timer.tv_usec;
        sleep_time_ref = sleep_time_ref + sleep_time_target;
        
        if(sleep_time_ref >= (timestamp + SLEEP_TIME_ADJUST)) {
            sleep_time_us = sleep_time_ref - timestamp - SLEEP_TIME_ADJUST;
        } else {
            sleep_time_us = 0;
            sleep_time_too_short = timestamp - sleep_time_ref;
        }
    } else {
        sleep_time_us = sleep_time_target;
    }    
    
    //uint32_t t = sleep_time_us;        
    //delayMicroseconds(t);
    esp_sleep_enable_timer_wakeup(sleep_time_us);
    esp_deep_sleep_start();
    
}

void Commander::powerPeripheral(bool _PowerOn)
{    
    if(_PowerOn)
    {
        digitalWrite(PIN_RELAY_PPWR_CTRL1, LOW);
        digitalWrite(PIN_RELAY_PPWR_CTRL2, LOW);
        delay(10);
        digitalWrite(PIN_RELAY_PPWR_CTRL1, HIGH);
        delay(100);
        digitalWrite(PIN_RELAY_PPWR_CTRL1, LOW);
        delay(10);
    } else
    {
        digitalWrite(PIN_RELAY_PPWR_CTRL1, LOW);
        digitalWrite(PIN_RELAY_PPWR_CTRL2, LOW);
        delay(10);
        digitalWrite(PIN_RELAY_PPWR_CTRL2, HIGH);
        delay(100);
        digitalWrite(PIN_RELAY_PPWR_CTRL2, LOW);
        delay(10);
    }
    delay(50);
}


void Commander::powerAux(bool _PowerOn)
{
    if(_PowerOn)
    {
        digitalWrite(PIN_RELAY_AUX_CTRL1, LOW);
        digitalWrite(PIN_RELAY_AUX_CTRL2, LOW);
        delay(10);
        digitalWrite(PIN_RELAY_AUX_CTRL2, HIGH);
        delay(100);
        digitalWrite(PIN_RELAY_AUX_CTRL2, LOW);
        delay(10);
    } else
    {
        digitalWrite(PIN_RELAY_AUX_CTRL1, LOW);
        digitalWrite(PIN_RELAY_AUX_CTRL2, LOW);
        delay(10);
        digitalWrite(PIN_RELAY_AUX_CTRL1, HIGH);
        delay(100);
        digitalWrite(PIN_RELAY_AUX_CTRL1, LOW);
        delay(10);
    }
}