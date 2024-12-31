/**
 * @file ESPRIC_RestartConditions.h
 * @brief Defines restart conditions and corresponding callbacks for the ESPRIC library.
 *
 * This header file contains definitions of restart conditions and their associated callbacks for
 * the ESPRIC (ESP32 Reboot Investigation and Context Integrity Check) library. These conditions
 * analyze ESP32-specific startup states such as reset reasons and wakeup causes. The conditions
 * are modular and can be extended as required.
 *
 * @details This file provides a collection of predefined restart conditions and callbacks that
 *          enable developers to execute specific logic based on detected startup scenarios. By
 *          modularizing these definitions, reusability and clarity are enhanced.
 */

#ifndef ESPRIC_RESTARTCONDITIONS_H
#define ESPRIC_RESTARTCONDITIONS_H

#include <ESPRIC.h>
#include <esp_system.h>
#include <esp_sleep.h>

/**
 * @brief Retrieves a vector of restart conditions and their corresponding callback functions.
 *
 * This function defines a set of conditions to analyze the startup state of an ESP32 device. The
 * conditions are used in conjunction with the ESPRIC class to execute specific actions based on
 * detected restart or wakeup scenarios.
 *
 * @note Supported conditions include:
 *  - Panic resets caused by unhandled exceptions.
 *  - Unknown reset reasons, typically after firmware updates.
 *  - Power-on resets triggered by device startup.
 *  - Wakeups caused by external signals such as GPIO activity.
 *
 * @return std::vector<ESPRIC::ESPRIC_Condition> A list of conditions and their callbacks.
 */
std::vector<ESPRIC::ESPRIC_Condition> getRestartConditions() {
    return {
        /**
         * @brief Detects a panic reset.
         *
         * @details Triggered when the reset reason is `ESP_RST_PANIC`. This reset typically
         *          occurs due to unhandled exceptions or critical errors, such as division by zero.
         *
         * @note The callback logs the panic event and halts the system indefinitely to ensure
         *       safety and debugging consistency.
         */
        {[]() { return esp_reset_reason() == ESP_RST_PANIC; }, 
         []() { 
             Serial.println("[ESPRIC] Panic reset detected. Unhandled exception occurred."); 
             Serial.println("[ESPRIC] System halting for safety."); 
             while (true); // Halt the system
         }},

        /**
         * @brief Detects an unknown reset reason.
         *
         * @details Triggered when the reset reason is `ESP_RST_UNKNOWN`. This reset typically
         *          occurs after firmware updates or unclassified errors.
         *
         * @note The callback logs the unknown reset reason for debugging purposes.
         */
        {[]() { return esp_reset_reason() == ESP_RST_UNKNOWN; }, 
         []() { 
             Serial.println("[ESPRIC] Reset reason could not be determined. Possible firmware update."); 
         }},

        /**
         * @brief Detects a power-on reset.
         *
         * @details Triggered when the reset reason is `ESP_RST_POWERON`. This indicates the
         *          device has been powered on or the reset button was pressed.
         *
         * @note The callback logs the power-on reset event for informational purposes.
         */
        {[]() { return esp_reset_reason() == ESP_RST_POWERON; }, 
         []() { 
             Serial.println("[ESPRIC] Power-on reset detected."); 
         }},

        /**
         * @brief Detects a wakeup caused by an external signal.
         *
         * @details Triggered when the wakeup cause is `ESP_SLEEP_WAKEUP_EXT0`. This indicates
         *          that the device was woken up by an external signal, such as a GPIO pin.
         *
         * @note The callback logs the wakeup event and can be used to trigger specific wakeup logic.
         * @see https://docs.espressif.com/projects/arduino-esp32/en/latest/api/deepsleep.html
         */
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0; }, 
         []() { 
             Serial.println("[ESPRIC] Wakeup by external signal detected."); 
         }}
    };
}

#endif // ESPRIC_RESTARTCONDITIONS_H
