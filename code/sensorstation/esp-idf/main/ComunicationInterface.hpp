/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ComunicationInterface.hpp
 * Author: marc
 *
 * Created on 23. Januar 2018, 23:22
 */

#ifndef COMUNICATIONINTERFACE_HPP
#define COMUNICATIONINTERFACE_HPP

class CommunicationInterface 
{
    public:
        virtual int setConfig(unsigned int _CMD_ID, void* _Args);
};

#endif /* COMUNICATIONINTERFACE_HPP */

