/* 
 * File:   Commands.h
* Author: Marc Schaefer <marc-schaefer.dev@highdynamics.org>
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

/* + + + + COMMAND: Authenticate + + + + */
    #define CMD_ID_AUTH 0
/* + + + + + + + + + + ACTION: identify + + + + + + + + + + */
        #define CMD_ACTION_ID_AUTH_IDENTIFY 0
        #define CMD_ACTION_ID_AUTH_REGISTER 1
/* + + + + + + + + + + + + + + + DATA: indentfy + + + + + + + + + + + + + + + */
            #define CMD_DATA_ID_IDENTIFY_DEVICE_ID 0
            #define CMD_DATA_ID_IDENTIFY_IP 1
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
        #define CMD_ACTION_ID_CONFIG_SET_MINUTES_SLEEP_TIME 0
        #define CMD_ACTION_ID_CONFIG_GET_MINUTES_SLEEP_TIME 1
        #define CMD_ACTION_ID_CONFIG_SET_NUMBER_SENSOR_RUNS 2
        #define CMD_ACTION_ID_CONFIG_GET_NUMBER_SENSOR_RUNS 3
        #define CMD_ACTION_ID_CONFIG_SET_NUMBER_SAMPLINGS 4
        #define CMD_ACTION_ID_CONFIG_GET_NUMBER_SAMPLINGS 5
        #define CMD_ACTION_ID_CONFIG_SET_TIME 6
        #define CMD_ACTION_ID_CONFIG_GET_TIME 7
/* + + + + + + + + + + + + + + + DATA:  + + + + + + + + + + + + + + + */
            /* Value of Action of - no data */
/* - - - - - - - - - - - - - - - DATA:  - - - - - - - - - - - - - - - */
/* - - - - - - - - - - ACTION:  - - - - - - - - - - */
/* - - - - COMMAND:  - - - - */

#endif /* COMMANDS_H */
