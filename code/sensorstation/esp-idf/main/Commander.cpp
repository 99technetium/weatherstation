/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Commander.cpp
 * Author: marc
 * 
 * Created on 23. Januar 2018, 23:08
 */

#include "Commander.h"

//#include "freertos/FreeRTOS.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "Arduino.h"
#include "IPAddress.h"
#include "Communicator.h"
#include <string>

using namespace std;

Commander::Commander()
{
    nvs_flash_init();
    tcpip_adapter_init();
    //ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
    initArduino();
    
    Serial.begin(115200);
    delay(10);
 
    std::string ssid     = "Apartment_EG_2.4GHz_new";
    std::string password = "5455922329870587";
    
    uint16_t port = 8080;
    IPAddress ip(192, 168, 5, 154);
    
    Communicator com(*this);
    com.start(ssid, password, ip, port);
    com.end();
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
