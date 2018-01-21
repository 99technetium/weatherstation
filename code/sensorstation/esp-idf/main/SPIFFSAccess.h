/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SPIFFSAccess.h
 * Author: marc
 *
 * Created on 20. Januar 2018, 03:52
 */

#include "FS.h"
#include "SPIFFS.h"

#ifndef SPIFFSACCESS_H
#define SPIFFSACCESS_H


class SPIFFSAccess {
public:
    void begin();
    void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
    void readFile(fs::FS &fs, const char * path);
    void writeFile(fs::FS &fs, const char * path, const char * message);
    void appendFile(fs::FS &fs, const char * path, const char * message);
    void renameFile(fs::FS &fs, const char * path1, const char * path2);
    void deleteFile(fs::FS &fs, const char * path);
    void testFileIO(fs::FS &fs, const char * path);
    SPIFFSAccess();
    SPIFFSAccess(const SPIFFSAccess& orig);
    virtual ~SPIFFSAccess();
private:

};

#endif /* SPIFFSACCESS_H */

