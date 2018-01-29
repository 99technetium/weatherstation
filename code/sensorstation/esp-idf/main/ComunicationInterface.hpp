/* 
 * File:   ComunicationInterface.hpp
* Author: Marc Schaefer <marc-schaefer.dev@highdynamics.org>
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

