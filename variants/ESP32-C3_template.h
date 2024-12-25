// ESP32-C3 specific reset and wakeup causes
#ifndef ESP32_C3_TEMPLATE_H
#define ESP32_C3_TEMPLATE_H

#include <ESP32StartupErrorAnalyzer.h>

// Define specific reset and wakeup reasons for ESP32-C3
std::vector<ESP32StartupErrorAnalyzer::ErrorCondition> getStartupConditions() {
    return {
        // Power-on reset (ESP32-C3)
        {[]() { return esp_reset_reason() == ESP_RST_POWERON; },
         []() { Serial.println("Power-On reset detected!"); }},
        
        // Software reset (ESP32-C3)
        {[]() { return esp_reset_reason() == ESP_RST_SW; },
         []() { Serial.println("Software reset detected!"); }},
        
        // Panic reset  (ESP32-C3)
        {[]() { return esp_reset_reason() == ESP_RST_PANIC; },
         []() { Serial.println("Panic reset detected!"); }},
        
        // Wake-up by external signal (ESP32-C3)
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0; },
         []() { Serial.println("Wake-up by external signal!"); }},
        
        // Wake-up by GPIO (ESP32-C3)
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_GPIO; },
         []() { Serial.println("Wake-up by GPIO!"); }},
        
        // "Wake-up by timer (ESP32-C3)
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER; },
         []() { Serial.println("Wake-up by timer!"); }}
    };
}

#endif // ESP32_C3_TEMPLATE_H
