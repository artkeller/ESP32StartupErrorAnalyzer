/**
 * @file ErrorCounterInRTC.ino
 * @brief Example usage of ESP32StartupErrorAnalyzer with RTC memory-based error counters.
 * 
 * This example demonstrates how to use the `ESP32StartupErrorAnalyzer` to track and count 
 * specific reset reasons and handle them using RTC memory to retain the counters across resets.
 */

#include <ESP32StartupErrorAnalyzer.h>

/**
 * @brief RTC memory storage for error counters.
 * 
 * These variables are stored in RTC memory, allowing their values to persist across resets 
 * unless explicitly reset or erased.
 */
 RTC_DATA_ATTR uint32_t panicResetCounter = 0;   ///< Counter for panic resets.
 RTC_DATA_ATTR uint32_t powerOnResetCounter = 0; ///< Counter for power-on resets.

/**
 * @brief Defines startup conditions and their associated callbacks.
 * 
 * @return A vector of `ErrorCondition` structures representing conditions and callbacks.
 * 
 * This function creates a list of conditions to detect specific reset reasons or wakeup events 
 * and associates them with actions such as incrementing counters or logging messages.
 */
std::vector<ESP32StartupErrorAnalyzer::ErrorCondition> getStartupConditions() {
    return {
        // Increment and report panic reset counter
        {[]() { return esp_reset_reason() == ESP_RST_PANIC; },
         []() {
             panicResetCounter++;
             Serial.printf("Panic reset detected! Counter: %d\n", panicResetCounter);
         }},
        // Increment and report power-on reset counter
        {[]() { return esp_reset_reason() == ESP_RST_POWERON; },
         []() {
             powerOnResetCounter++;
             Serial.printf("Power-on reset detected! Counter: %d\n", powerOnResetCounter);
         }},
        // Report external wakeup
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0; },
         []() { Serial.println("Wakeup detected from external signal."); }}
    };
}

/**
 * @brief Sets up the ESP32 and initializes the startup error analyzer.
 * 
 * The setup function initializes the serial connection, configures the startup conditions, 
 * and dynamically adds an additional condition to reset counters on a brownout event.
 */
void setup() {
    // Initialize the serial connection
    Serial.begin(115200);
    while (!Serial) {}; // Wait until the serial connection is ready (important for ESP32-C3)
    Serial.println("Firmware started: ESP32StartupErrorAnalyzer - ErrorCounterInRTC");

    // Create the error analyzer with predefined startup conditions
    ESP32StartupErrorAnalyzer analyzer(getStartupConditions());

    // Add a dynamic condition to reset counters on brownout detection
    analyzer.addCondition(
        []() { return esp_reset_reason() == ESP_RST_BROWNOUT; },
        []() {
            panicResetCounter = 0;
            powerOnResetCounter = 0;
            Serial.println("Brownout detected! Error counters reset.");
        }
    );

    // Start analyzing conditions and execute corresponding callbacks
    Serial.println("Start Analyzer...");
    analyzer.analyze();  
    Serial.println("Ready!");
}

/**
 * @brief Main loop of the program.
 * 
 * This function contains the primary logic of the program. In this example, it is left empty.
 */
void loop() {
    // Main logic
}
