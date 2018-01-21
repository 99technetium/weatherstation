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


class Transmitter {
public:
    Transmitter(const Transmitter& orig);
    Transmitter(std::string _SSID, std::string _Key);
    virtual ~Transmitter();
    int connect();
    int disconnect();
private:
    int ifup();
    int ifdown();
    static esp_err_t event_handler(void *ctx, system_event_t *event);
    
    std::string tSSID, tKey;
};

#endif /* TRANSMITTER_H */

