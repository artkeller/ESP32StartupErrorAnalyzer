/**
 * @file AddConditionsInSetup.ino
 * @brief Example demonstrating the dynamic addition of startup conditions in the setup function.
 * 
 * This example extends the functionality of `ESP32StartupErrorAnalyzer` by dynamically adding 
 * conditions to analyze during runtime. It combines conditions defined in an external file 
 * with additional conditions specified directly in the setup function.
 */

#include <ESP32StartupErrorAnalyzer.h>
#include "RestartConditions.h"

/**
 * @brief Main setup function to initialize the firmware and start condition analysis.
 * 
 * This function initializes the serial connection, creates an instance of `ESP32StartupErrorAnalyzer`, 
 * and adds additional conditions to be analyzed during startup. It demonstrates both static 
 * conditions (from a header file) and dynamic conditions (added in the setup function).
 */
void setup() {
    // Initialize the serial connection
    Serial.begin(115200);
    while (!Serial) {}; // Wait for the serial connection to be ready (important for some devices like ESP32-C3)
    Serial.println("Firmware started: ESP32StartupErrorAnalyzer - AddConditionsInSetup");

    // Initialize the restart error analyzer with predefined conditions
    ESP32StartupErrorAnalyzer analyzer(getReatartConditions());

    /**
     * @brief Dynamically add a condition for deep-sleep reset.
     * 
     * This condition is triggered if the reset reason is `ESP_RST_DEEPSLEEP`.
     * The callback logs a message indicating that a deep-sleep reset was detected.
     */
    analyzer.addCondition(
        []() { return esp_reset_reason() == ESP_RST_DEEPSLEEP; }, 
        []() { Serial.println("Deep-sleep reset detected."); }
    );

    /**
     * @brief Dynamically add a condition for software reset.
     * 
     * This condition is triggered if the reset reason is `ESP_RST_SW`.
     * The callback logs a message indicating that a software reset was detected.
     */
    analyzer.addCondition(
        []() { return esp_reset_reason() == ESP_RST_SW; }, 
        []() { Serial.println("Software reset detected."); }
    );

    // Start analyzing conditions and execute corresponding callbacks
    Serial.println("Start Analyzer...");
    analyzer.analyze();  
    Serial.println("Ready!");
}

/**
 * @brief Main loop function.
 * 
 * This function is intentionally left empty for simplicity, 
 * as the focus of this example is on the setup function and condition analysis.
 */
void loop() {
    // Main logic
}
