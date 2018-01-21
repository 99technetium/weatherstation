/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Transmitter.cpp
 * Author: marc
 * 
 * Created on 21. Januar 2018, 20:49
 */

#include <string>

#include "Transmitter.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event_loop.h"


Transmitter::Transmitter(const Transmitter& orig) 
{
}

Transmitter::Transmitter(std::string _SSID, std::string _Key) 
{
    tSSID = _SSID;
    tKey = _Key;    
}

Transmitter::~Transmitter() 
{
}

static esp_err_t Transmitter::event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
	ESP_LOGI(TAG, "SYSTEM_EVENT_STA_START");
	ESP_ERROR_CHECK(esp_wifi_connect());
	break;
    case SYSTEM_EVENT_STA_GOT_IP:
	ESP_LOGI(TAG, "SYSTEM_EVENT_STA_GOT_IP");
	ESP_LOGI(TAG, "got ip:%s\n",
		ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
	ESP_LOGI(TAG, "SYSTEM_EVENT_STA_DISCONNECTED");
	ESP_ERROR_CHECK(esp_wifi_connect());
	break;
    default:
        break;
    }
    return ESP_OK;
}

int Transmitter::ifup()
{
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));
    
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    wifi_config_t wifi_config = {
	.sta = {
	    .ssid = tSSID.c_str(),
	    .password = tKey.c_str(),
	},
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}

int Transmitter::ifdown()
{
    ESP_ERROR_CHECK(esp_wifi_stop());
    ESP_ERROR_CHECK(esp_wifi_deinit());
    
}

int Transmitter::connect() 
{
    ifup();
    ESP_ERROR_CHECK(esp_wifi_connect());
}

int Transmitter::disconnect() 
{
    ESP_ERROR_CHECK(esp_wifi_disconnect());
    ifdown();    
}