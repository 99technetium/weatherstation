/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Commands.h
 * Author: marc
 *
 * Created on 23. Januar 2018, 16:12
 */

#ifndef COMMANDS_H
#define COMMANDS_H

/*
 * 
 *  {CMD:[CMD_ID:[CMD_ACTION_ID_x:[CMD_DATA_x_y]]}
 *  x = Command
 *  y = Action
 * 
 *  CMD_JSON_KEY[
 *      CMD_ID[
 *          CMD_ACTION_ID_x[
 *              CMD_DATA_x_y[]
 *          ]
 *      ]
 *  ]
 *  
 */
#define CMD_JSON_KEY "cmd"

/* + + + + COMMAND: Handshake + + + + */
    #define CMD_ID_HANDSHAKE 0
/* + + + + + + + + + + ACTION: sign on + + + + + + + + + + */
        #define CMD_ACTION_ID_HANDSHAKE_SIGNON 0
        #define CMD_ACTION_ID_HANDSHAKE_CONFIRM 1
/* + + + + + + + + + + + + + + + DATA: sign on / confirm + + + + + + + + + + + + + + + */
            #define CMD_DATA_ID_HANDSHAKE_DEVICE_ID 0
            #define CMD_DATA_ID_HANDSHAKE_IP 1
/* - - - - - - - - - - - - - - - DATA: sign on - - - - - - - - - - - - - - - */
/* - - - - - - - - - - ACTION: sign on - - - - - - - - - - */
/* - - - - COMMAND: Handshake - - - - */

/* + + + + COMMAND: Data + + + + */
    #define CMD_ID_DATA 1
/* + + + + + + + + + + ACTION: Sensor data + + + + + + + + + + */    
        #define CMD_ACTION_ID_DATA_ADD_SENSORDATA 0 /*Array*/
        #define CMD_ACTION_ID_DATA_GET_SENSORDATA 1 
/* + + + + + + + + + + + + + + + DATA: Sensor data + + + + + + + + + + + + + + + */
            /* Key: Sensor ID, Value: Sensor Data array */
/* - - - - - - - - - - - - - - - DATA: Sensor data - - - - - - - - - - - - - - - */
/* - - - - - - - - - - ACTION: Add sensor data - - - - - - - - - - */
/* - - - - COMMAND: Send Data - - - - */

/* + + + + COMMAND: Config + + + + */
    #define CMD_ID_CONFIG 3
/* + + + + + + + + + + ACTION: Sleep time + + + + + + + + + + */
        #define CMD_ACTION_ID_CONFIG_SET_SLEEP_TIME 0
        #define CMD_ACTION_ID_CONFIG_GET_SLEEP_TIME 1
/* + + + + + + + + + + + + + + + DATA:  + + + + + + + + + + + + + + + */
            /* Value of Action of - no data */
/* - - - - - - - - - - - - - - - DATA:  - - - - - - - - - - - - - - - */
/* - - - - - - - - - - ACTION:  - - - - - - - - - - */
/* - - - - COMMAND:  - - - - */

#endif /* COMMANDS_H */
