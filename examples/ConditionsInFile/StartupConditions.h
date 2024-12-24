#ifndef STARTUPCONDITIONS_H
#define STARTUPCONDITIONS_H

#include <ESP32StartupErrorAnalyzer.h>
#include <esp_system.h>
#include <esp_sleep.h>

std::vector<ESP32StartupErrorAnalyzer::ErrorCondition> getStartupConditions() {
    return {
        {[]() { return esp_reset_reason() == ESP_RST_PANIC; }, []() { Serial.println("Panik-Reset erkannt."); }},
        {[]() { return esp_reset_reason() == ESP_RST_POWERON; }, []() { Serial.println("Power-On erkannt."); }},
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0; }, []() { Serial.println("Wakeup durch externes Signal."); }}
    };
}

#endif
