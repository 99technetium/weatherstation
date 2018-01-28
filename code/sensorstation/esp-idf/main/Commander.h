/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Commander.h
 * Author: marc
 *
 * Created on 23. Januar 2018, 23:08
 */

#ifndef COMMANDER_H
#define COMMANDER_H

#include "ComunicationInterface.hpp"


class Commander: public CommunicationInterface {
public:
    Commander();
    Commander(const Commander& orig);
    virtual ~Commander();
    virtual int setConfig(unsigned int _CMD_ID, void* _Args);
    void powerPeripheral(bool _PowerOn);
    void powerAux(bool _PowerOn);
private:
    void initConfig();
    void sleep(); 
};

#endif /* COMMANDER_H */

