/**
 * @file RestartConditions.h
 * @brief Definition of restart conditions and corresponding callbacks for ESP32StartupErrorAnalyzer.
 * 
 * This file provides a modular and reusable way to define startup conditions and their associated 
 * callback functions for use with the ESP32StartupErrorAnalyzer. These conditions cover various 
 * reset reasons and wakeup causes specific to ESP32-based systems.
 */

#ifndef STARTUPCONDITIONS_H
#define STARTUPCONDITIONS_H

#include <ESP32StartupErrorAnalyzer.h>
#include <esp_system.h>
#include <esp_sleep.h>

static RTC_DATA_ATTR int wakeupCounter; // wird nach ESP_RST_POWERON mit 0 initialisiert
const uint32_t MAX_WAKEUP_COUNT = 3; // Maximale Anzahl Wakeups vor Reset

/**
 * @brief Retrieves a list of startup conditions and their corresponding callback functions.
 * 
 * This function defines a vector of `ESP32StartupErrorAnalyzer::ErrorCondition` objects, 
 * each specifying a condition to check and a callback to execute when the condition is met. 
 * It includes checks for various reset reasons (e.g., panic, power-on) and wakeup causes 
 * (e.g., external signals).
 * 
 * @return A vector of `ESP32StartupErrorAnalyzer::ErrorCondition` objects.
 */
std::vector<ESP32StartupErrorAnalyzer::ErrorCondition> getStartupConditions() {
    return {
        /**
         * @brief Condition for panic reset.
         * @details This condition is triggered if the reset reason is `ESP_RST_PANIC`. 
         *          The callback logs a message indicating that a panic reset was detected.
         */
        {[]() { return esp_reset_reason() == ESP_RST_PANIC; }, 
         []() { Serial.println("Panic reset detected."); }},
         
        /**
         * @brief Condition for unknown reset reason.
         * @details This condition is triggered if the reset reason cannot be determined. 
         *          The callback logs a message stating that the reset reason is unknown.
         */
        {[]() { return esp_reset_reason() == ESP_RST_UNKNOWN; }, 
         []() { Serial.println("Reset reason could not be determined."); }},

 /**
         * @brief Condition for Software-Reset durch `esp_restart`
         * @details This condition is triggered if the reset reason cannot be determined. 
         *          The callback logs a message stating that the reset reason is unknown.
         */
        {[]() { return esp_reset_reason() == ESP_RST_SW; }, 
         []() { 
                wakeupCounter = 1;
                Serial.println("Reset reason by esp_restart."); 
                Serial.printf("Aktueller Wakeup-Zähler: %d\n", wakeupCounter);
                }},
         
        /**
         * @brief Condition for power-on reset.
         * @details This condition is triggered if the reset reason is `ESP_RST_POWERON`. 
         *          The callback logs a message indicating that a power-on event was detected.
         */
        {[]() { return esp_reset_reason() == ESP_RST_POWERON; }, 
         []() { 
                wakeupCounter = 1;
                Serial.println("Power-on detected."); 
                Serial.printf("Aktueller Wakeup-Zähler: %d\n", wakeupCounter);
                }},
         
        /**
         * @brief Condition for wakeup by external signal.
         * @details This condition is triggered if the wakeup cause is `ESP_SLEEP_WAKEUP_EXT0`. 
         *          The callback logs a message indicating that the system was woken up by an external signal.
         */
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER; }, 
         []() { 
                wakeupCounter++;
                Serial.println("Wakeup by timer detected."); 
                Serial.printf("Aktueller Wakeup-Zähler: %d\n", wakeupCounter);
                if (wakeupCounter >= MAX_WAKEUP_COUNT) {
                    wakeupCounter = 0; // Zurücksetzen
                    Serial.println("Maximale Anzahl Wakeups erreicht.");
                }
                }}
    };
}

#endif // STARTUPCONDITIONS_H
