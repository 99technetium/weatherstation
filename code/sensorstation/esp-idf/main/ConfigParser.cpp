/* 
 * File:   ConfigParser.cpp
 * Author: Marc Schaefer <marc-schaefer.dev@highdynamics.org>
 * 
 * Created on 20. Januar 2018, 04:32
 */
#include "ConfigParser.h"

static const char *TAG = "configparser";

ConfigParser::ConfigParser() {
    //SPIFFSAccess spiffs_access;
    //spiffs_access.begin();
    esp_vfs_spiffs_conf_t conf = {
      .base_path = "/spiffs",
      .partition_label = NULL,
      .max_files = 5,
      .format_if_mount_failed = false
    };
    
    Serial.print("Mounting spiffs...");
    // Use settings defined above to initialize and mount SPIFFS filesystem.
    // Note: esp_vfs_spiffs_register is an all-in-one convenience function.
    esp_err_t ret = esp_vfs_spiffs_register(&conf);      
    
    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            Serial.println("Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            Serial.println("Failed to find SPIFFS partition");
        } else {
            Serial.print("Failed to initialize SPIFFS: ");
            Serial.println(ret);
        }
        return;
    }
    Serial.println("successful.");    
    
    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information");
    } else {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }
    
    
}

ConfigParser::ConfigParser(const ConfigParser& orig) {
}

ConfigParser::~ConfigParser() {
}

unsigned int ConfigParser::countLines(std::string const& _filename)
{
    Serial.print("Counting lines of file: ");
    Serial.println(_filename.c_str());
    
    

    /*
    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("Failed to open file for reading");
        return -1;
    }
     * */
    
    
    unsigned int lines = 0;
    std::ifstream f( _filename.c_str() );
    if( !f.is_open() )
        throw std::domain_error( "Unable to load input file: " + _filename );

    std::string line;
    char c;
    while( f.get(c) ) {
        Serial.write(c);        
    }
        Serial.print("Done reading lines. Number of lines: ");
        Serial.print(lines);
    
/*
    std::ifstream infile(path);
    if( !infile  ) {
        Serial.println("Can't open file!");
    } else {
        Serial.println("File opened.");
    }
    
    std::string line;
    while (std::getline(infile, line))
    {
        lines++;
        Serial.print("Line ");
        Serial.print(lines);
        Serial.print(": ");
        Serial.println(line.c_str());
        std::istringstream iss(line);
        int a, b;
        if (!(iss >> a >> b)) { break; } // error
    }
        */
    return lines;
}

