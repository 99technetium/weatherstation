#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "freertos/event_groups.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "Arduino.h"
#include "HTTPClient.h"
#include "SPIFFSAccess.h"
#include "ConfigParser.h"
#include "esp_err.h"
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"
#include <WiFi.h>


const char* ssid     = "Apartment_EG_2.4GHz_new";
const char* password = "5455922329870587";

const char* host = "data.sparkfun.com";
const char* streamId   = "....................";
const char* privateKey = "....................";

extern "C" void app_main(void)
{
    nvs_flash_init();
    tcpip_adapter_init();
    //ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
    initArduino();
    
    Serial.begin(115200);
    delay(10);

    
    /*
    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    */    
    
    /*
    ConfigParser cfg;
    cfg.countLines("/spiffs/sensors.config");
    */
    SPIFFSAccess spiffs;
    spiffs.begin();
    spiffs.listDir(SPIFFS, "/", 0);
    spiffs.writeFile(SPIFFS, "/test.txt", "Das ist ein Test");
    spiffs.readFile(SPIFFS, "/test.txt");
    spiffs.readFile(SPIFFS, "/sensors.config");
    /*
    while(1) {
        loop();
        delay(2000);
    }
     * */
}

int value = 0;

void loop()
{
    Serial.println("Reading battery voltage...");
    int value = -1;
    value = analogRead(GPIO_NUM_2);
    Serial.print("Value:");
    Serial.println(value);
    double mV_batt = 1.709629933929*value;
    String mV_batt_str = String(mV_batt, 2);
    String mV_batt_label = mV_batt_str + " mV";
    Serial.println(mV_batt_label);
}

void wifi_connect()
{
                
    delay(5000);
    ++value;

    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    // We now create a URI for the request
    String url = "/input/";
    url += streamId;
    url += "?private_key=";
    url += privateKey;
    url += "&value=";
    url += value;

    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
    }

    Serial.println();
    Serial.println("closing connection");
    
}