/* 
 * File:   Commander.h
 * Author: Marc Schaefer <marc-schaefer.dev@highdynamics.org>
 *
 * Created on 23. Januar 2018, 23:08
 */

#ifndef COMMANDER_H
#define COMMANDER_H

#include "Communicator.h"
#include "ComunicationInterface.hpp"
#include "Prober.hpp"
#include "Pinmap.hpp"

#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_attr.h"
#include "esp_sleep.h"

#include "Arduino.h"
#include "IPAddress.h"

#include <sys/time.h>
#include <string>
#include <Preferences.h>

#define SLEEP_TIME_ADJUST 15    // Time in us needed for calculation of next sleep time

#define FACTOR_MIN_TO_US 60000000

#define PREF_KEY_INIT           "config_init"
#define PREF_KEY_SSID           "wifi_ssid"
#define PREF_KEY_WIFIKEY        "wifi_key"
#define PREF_KEY_SRV_PORT       "srv_port"
#define PREF_KEY_SRV_IP         "srv_ip"
#define PREF_KEY_SLEEPTIME      "sleeptime"
#define PREF_KEY_NUMBER_CYCLES  "number_cycles"
#define PREF_KEY_NUMBER_SAMPLES "number_samples"

class Commander: public CommunicationInterface {
public:
    Commander();
    Commander(const Commander& orig);
    virtual ~Commander();
    virtual int setConfig(unsigned int _CMD_ID, void* _Args);
    void powerPeripheral(bool _PowerOn);
    void powerAux(bool _PowerOn);
private:
    void init();
    void initConfig();
    void sleep(); 
};

#endif /* COMMANDER_H */

