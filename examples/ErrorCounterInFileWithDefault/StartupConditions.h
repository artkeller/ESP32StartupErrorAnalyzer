#ifndef STARTUPCONDITIONS_H
#define STARTUPCONDITIONS_H

#include <Preferences.h>
#include <vector>
#include <ESP32StartupErrorAnalyzer.h>

// Global counters for tracking different reset events
uint32_t panicResetCounter = 0;       ///< Counter for panic resets
uint32_t powerOnResetCounter = 0;    ///< Counter for power-on resets
uint32_t unknownResetCounter = 0;   ///< Counter for unknown resets

// Preferences object for Non-Volatile Storage (NVS)
Preferences preferences;

/**
 * @brief Loads error counters from Non-Volatile Storage (NVS).
 * 
 * This function initializes the preferences namespace and retrieves the values
 * of the error counters. If the namespace cannot be opened, the function returns false.
 * 
 * @return true if the counters are successfully loaded, false otherwise.
 */
bool loadCountersFromNVS() {
    if (!preferences.begin("error_counters", true)) {
        return false;
    }

    panicResetCounter = preferences.getUInt("panicCounter", 0);
    powerOnResetCounter = preferences.getUInt("powerOnCounter", 0);
    unknownResetCounter = preferences.getUInt("unknownCounter", 0);

    preferences.end();
    return true;
}

/**
 * @brief Saves error counters to Non-Volatile Storage (NVS).
 * 
 * This function stores the current values of the error counters in the preferences namespace.
 * If the namespace cannot be opened, the function returns false.
 * 
 * @return true if the counters are successfully saved, false otherwise.
 */
bool saveCountersToNVS() {
    if (!preferences.begin("error_counters", false)) {
        return false;
    }

    preferences.putUInt("panicCounter", panicResetCounter);
    preferences.putUInt("powerOnCounter", powerOnResetCounter);
    preferences.putUInt("unknownCounter", unknownResetCounter);

    preferences.end();
    return true;
}

/**
 * @brief Resets all error counters to zero and saves them to NVS.
 * 
 * This function clears the values of all error counters and ensures they are saved persistently.
 */
void resetAllCounters() {
    panicResetCounter = 0;
    powerOnResetCounter = 0;
    unknownResetCounter = 0;
    saveCountersToNVS();
}

/**
 * @brief Increments the counter for unknown resets and saves it to NVS.
 * 
 * This function handles cases where the reset reason is not recognized by the system.
 */
void incrementUnknownResetCounter() {
    unknownResetCounter++;
    saveCountersToNVS();
}

/**
 * @brief Retrieves the startup conditions for analyzing reset events.
 * 
 * This function returns a vector of error conditions, each defined by a predicate 
 * (to check the reset reason) and an associated action (to handle the reset).
 * 
 * - Panic reset: Increments the panic reset counter and logs the event.
 * - Power-on reset: Increments the power-on reset counter and logs the event.
 * 
 * @return A vector of `ErrorCondition` objects defining the startup conditions.
 */
std::vector<ESP32StartupErrorAnalyzer::ErrorCondition> getStartupConditions() {
    return {
        // Condition for panic reset
        {[]() { return esp_reset_reason() == ESP_RST_PANIC; },
         []() {
             panicResetCounter++;
             Serial.printf("Panic reset detected! Counter: %lu\n", panicResetCounter);
             saveCountersToNVS();
         }},
        // Condition for power-on reset
        {[]() { return esp_reset_reason() == ESP_RST_POWERON; },
         []() {
             powerOnResetCounter++;
             Serial.printf("Power-on reset detected! Counter: %lu\n", powerOnResetCounter);
             saveCountersToNVS();
         }}
    };
}

#endif // STARTUPCONDITIONS_H
