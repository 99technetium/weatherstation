/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Transmitter.h
 * Author: marc
 *
 * Created on 21. Januar 2018, 20:49
 */

#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <string>
#include "esp_log.h"
#include "esp_event_loop.h"


class Transmitter {
public:
    Transmitter(const Transmitter& orig);
    Transmitter();
    virtual ~Transmitter();
    int connect();
    int disconnect();
    void init(std::string _SSID, std::string _Key);
private:
    int ifup();
    int ifdown();
    static esp_err_t event_handler(void *ctx, system_event_t *event);
    
    std::string tSSID, tKey;
};

#endif /* TRANSMITTER_H */

