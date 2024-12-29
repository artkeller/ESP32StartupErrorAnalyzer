/**
 * @file RestartConditions.h
 * @brief Definition of restart conditions and corresponding callbacks for ESP32StartupErrorAnalyzer.
 * 
 * This file provides a modular and reusable way to define restart conditions and their associated 
 * callback functions for use with the ESP32StartupErrorAnalyzer. These conditions cover various 
 * reset reasons and wakeup causes specific to ESP32-based systems.
 */

#ifndef RESTARTCONDITIONS_H
#define RESTARTCONDITIONS_H

#include <ESP32StartupErrorAnalyzer.h>
#include <esp_system.h>
#include <esp_sleep.h>

/**
 * @brief Retrieves a list of restart conditions and their corresponding callback functions.
 * 
 * This function defines a vector of `ESP32StartupErrorAnalyzer::ErrorCondition` objects, 
 * each specifying a condition to check and a callback to execute when the condition is met. 
 * It includes checks for various reset reasons (e.g., panic, power-on) and wakeup causes 
 * (e.g., external signals).
 * 
 * @return A vector of `ESP32StartupErrorAnalyzer::ErrorCondition` objects.
 */
std::vector<ESP32StartupErrorAnalyzer::ErrorCondition> getRestartConditions() {
    return {
        /**
         * @brief Condition for panic reset.
         * @details This condition is triggered if the reset reason is `ESP_RST_PANIC`. 
         *          The callback logs a message indicating that a panic reset was detected.
         *          This state is caused by unhandled exceptions or other forbidden statements 
         *          such as 1/x with x=0.
         */
        {[]() { return esp_reset_reason() == ESP_RST_PANIC; }, 
         []() { Serial.println("Panic reset detected."); }},
         
        /**
         * @brief Condition for unknown reset reason.
         * @details This condition is triggered if the reset reason cannot be determined. 
         *          The callback logs a message stating that the reset reason is unknown.
         *          This is a typical reason that occurs after a sketch update.
         */
        {[]() { return esp_reset_reason() == ESP_RST_UNKNOWN; }, 
         []() { Serial.println("Reset reason could not be determined."); }},
         
        /**
         * @brief Condition for power-on reset.
         * @details This condition is triggered if the reset reason is `ESP_RST_POWERON`. 
         *          The callback logs a message indicating that a power-on event was detected.
         *          Powering up or pressing the reset button will trigger this cause.
         */
        {[]() { return esp_reset_reason() == ESP_RST_POWERON; }, 
         []() { Serial.println("Power-on detected."); }},
         
        /**
         * @brief Condition for wakeup by external signal.
         * @details This condition is triggered if the wakeup cause is `ESP_SLEEP_WAKEUP_EXT0`. 
         *          The callback logs a message indicating that the system was woken up by an external signal.
         *          
         *          More see https://docs.espressif.com/projects/arduino-esp32/en/latest/api/deepsleep.html
         */
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0; }, 
         []() { Serial.println("Wakeup by external signal detected."); }}
    };
}

#endif // RESTARTCONDITIONS_H
