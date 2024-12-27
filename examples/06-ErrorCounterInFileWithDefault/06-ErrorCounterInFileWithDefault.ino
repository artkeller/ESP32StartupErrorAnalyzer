/**
 * @file ErrorCounterInFileWithDefault.ino
 * @brief Example sketch for tracking and handling reset events on an ESP32.
 * 
 * This sketch demonstrates the usage of the ESP32StartupErrorAnalyzer library
 * with Non-Volatile Storage (NVS) for counting and analyzing reset reasons.
 * Reset events like panic resets, power-on resets, and unknown resets are tracked.
 * The counters are stored persistently in NVS and can be reset under specific conditions.
 */

#include "StartupConditions.h"

/**
 * @brief The setup function initializes the system and performs startup error analysis.
 * 
 * This function initializes the serial interface for debugging, loads error counters 
 * from NVS, and sets up an ESP32StartupErrorAnalyzer instance with predefined startup 
 * conditions. If an unknown reset occurs or a brownout is detected, respective actions 
 * are taken to handle these events.
 */
void setup() {
    // Initialize the serial interface for debugging purposes
    Serial.begin(115200);
    while (!Serial) {}; // Wait for the serial interface to be ready

    Serial.println("Firmware started: ESP32StartupErrorAnalyzer - ErrorCounterInFileWithDefault");

    /**
     * @brief Load counters from NVS storage.
     * 
     * If loading fails, all counters are reset to zero. This ensures the system has
     * a valid initial state for tracking errors.
     */
    if (!loadCountersFromNVS()) {
        Serial.println("Error loading counters! Initializing all counters to zero.");
        resetAllCounters();
    }

    /**
     * @brief Instantiate the error analyzer with predefined startup conditions.
     * 
     * The analyzer evaluates specific reset conditions, such as panic and power-on resets.
     * A default callback is used to handle unknown reset reasons.
     */
    ESP32StartupErrorAnalyzer analyzer(
        getStartupConditions(),
        []() { 
            // Default callback for handling unknown reset reasons
            incrementUnknownResetCounter();
            Serial.printf("Unknown reset reason! Counter: %u\n", unknownResetCounter);
        }
    );

    /**
     * @brief Add a condition to reset all counters when a brownout is detected.
     * 
     * A brownout event indicates a significant voltage drop, requiring the system
     * to reset all error counters to maintain data integrity.
     */
    analyzer.addCondition(
        []() { return esp_reset_reason() == ESP_RST_BROWNOUT; },
        []() {
            resetAllCounters();
            Serial.println("Brownout detected! All counters reset.");
        }
    );

    // Analyze the current reset reason and execute corresponding actions
    Serial.println("Analyzing reset conditions...");
    analyzer.analyze();

    /**
     * @brief Save the updated counters back to NVS storage.
     * 
     * This ensures that the counter values persist across device reboots and resets.
     */
    if (!saveCountersToNVS()) {
        Serial.println("Error saving counters to NVS!");
    }

    Serial.println("Ready!");
}

/**
 * @brief The loop function is the main application logic placeholder.
 * 
 * In this example, the loop function does not perform any actions, as the
 * focus is on analyzing and handling startup conditions in the setup phase.
 */
void loop() {
    // Main application logic (not used in this example)
}
