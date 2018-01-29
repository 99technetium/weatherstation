#include "Commander.h"

#include "FS.h"
#include "SPIFFS.h"

extern "C" void app_main(void)
{

    nvs_flash_init();
    tcpip_adapter_init();
    //ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
    //initArduino();
    
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
    
    SPIFFSAccess spiffs;
    spiffs.begin();
    spiffs.listDir(SPIFFS, "/", 0);
    spiffs.writeFile(SPIFFS, "/test.txt", "Das ist ein Test");
    spiffs.readFile(SPIFFS, "/test.txt");
    spiffs.readFile(SPIFFS, "/sensors.config");
    */
    
    /*
    delay(2000);
    
        digitalWrite(PIN_RELAY_AUX_CTRL2, LOW);
        delay(10);
        digitalWrite(PIN_RELAY_AUX_CTRL1, HIGH);
        delay(100);
        digitalWrite(PIN_RELAY_AUX_CTRL1, LOW);
        delay(2000);
        digitalWrite(PIN_RELAY_AUX_CTRL2, HIGH);
        delay(100);
        digitalWrite(PIN_RELAY_AUX_CTRL2, LOW);
    */
    
    Commander com;    
}

/*

void loop()
{    
    timeval timer;
    
    if(gettimeofday(&timer, NULL) < 0) 
    {
        Serial.println("Error getting time!");
    } else {
        Serial.print("Time: ");
        Serial.print(timer.tv_sec);
        Serial.print(".");
        Serial.println(timer.tv_usec);
    }   
    
}
*/
/*
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
 * */