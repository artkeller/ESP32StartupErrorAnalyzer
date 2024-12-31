/**
 * @file ESPRIC_RestartConditions.h
 * @brief Definition of restart conditions and corresponding callbacks for ESPRIC library.
 * 
 * This header file defines the restart conditions and associated callbacks for the 
 * ESPRIC (ESP32 Reboot Investigation and Context Integrity Check) library. The conditions 
 * cover various reset reasons and wakeup causes specific to ESP32-based systems. 
 * By separating these definitions into a dedicated file, modularity and reusability 
 * are significantly improved.
 */

#ifndef ESPRIC_RESTARTCONDITIONS_H
#define ESPRIC_RESTARTCONDITIONS_H

#include <ESPRIC.h>
#include <esp_system.h>
#include <esp_sleep.h>

/**
 * @namespace ESPRIC
 * @brief Namespace for all ESPRIC-related functionality.
 */
namespace ESPRIC {

/**
 * @brief Retrieves a vector of restart conditions and their corresponding callback functions.
 * 
 * This function defines a set of conditions and their associated callbacks 
 * for analyzing the startup state of an ESP32 device. These conditions are used 
 * in conjunction with the `ESPRIC::ErrorAnalyzer` to execute specific actions 
 * based on the detected restart or wakeup scenario.
 * 
 * @note The conditions currently cover:
 * - Panic resets caused by unhandled exceptions.
 * - Unknown reset reasons, often occurring after firmware updates.
 * - Power-on resets triggered by device startup.
 * - Wakeups caused by external signals (e.g., GPIO).
 * 
 * @return std::vector<ESPRIC::ErrorAnalyzer::ErrorCondition> 
 * A vector of conditions to be analyzed by the `ESPRIC::ErrorAnalyzer`.
 */
std::vector<ESPRIC::ErrorAnalyzer::ErrorCondition> getRestartConditions() {
    return {
        /**
         * @brief Condition for panic reset.
         * @details Triggered if the reset reason is `ESP_RST_PANIC`. This type of reset occurs 
         * due to unhandled exceptions or forbidden operations like division by zero.
         */
        {[]() { return esp_reset_reason() == ESP_RST_PANIC; }, 
         []() { 
             Serial.println("[ESPRIC] Panic reset detected. Unhandled exception occurred."); 
             Serial.println("[ESPRIC] System halting for safety."); 
             while (true);  // Halt the system
         }},
         
        /**
         * @brief Condition for unknown reset reason.
         * @details Triggered if the reset reason cannot be determined. This is a common reset 
         * reason after a firmware update or an unknown error.
         */
        {[]() { return esp_reset_reason() == ESP_RST_UNKNOWN; }, 
         []() { Serial.println("[ESPRIC] Reset reason could not be determined. Possible firmware update."); }},
         
        /**
         * @brief Condition for power-on reset.
         * @details Triggered if the reset reason is `ESP_RST_POWERON`. Indicates the device 
         * powered up or the reset button was pressed.
         */
        {[]() { return esp_reset_reason() == ESP_RST_POWERON; }, 
         []() { Serial.println("[ESPRIC] Power-on reset detected."); }},
         
        /**
         * @brief Condition for wakeup by external signal.
         * @details Triggered if the wakeup cause is `ESP_SLEEP_WAKEUP_EXT0`. Indicates that 
         * the device was woken up by an external signal, such as a GPIO pin.
         * 
         * @see https://docs.espressif.com/projects/arduino-esp32/en/latest/api/deepsleep.html
         */
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0; }, 
         []() { Serial.println("[ESPRIC] Wakeup by external signal detected."); }}
    };
}

} // namespace ESPRIC

#endif // ESPRIC_RESTARTCONDITIONS_H
