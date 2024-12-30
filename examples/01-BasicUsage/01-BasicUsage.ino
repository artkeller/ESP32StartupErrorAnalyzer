/**
 * @file 01-BasicUsage.ino
 * @brief Example of how to use ESPRIC to analyze the cause of the reset.
 * 
 * This example demonstrates how to use the ESPRIC library to define 
 * conditions for analyzing the cause of a reset and to register callback 
 * functions that execute specific actions when these conditions are met.
 * The results are output via the serial interface.
 */

#include <ESPRIC.h>

/**
 * @brief Defines the conditions and their associated callback functions.
 * 
 * This function returns a list of conditions that the ESPRIC analyzer will evaluate. 
 * Each condition is represented by a pair of lambda functions:
 * 
 * - **Condition Function**: A function that evaluates a specific condition and 
 *   returns `true` if the condition is met, or `false` otherwise.
 * - **Callback Function**: A function that is executed if the condition function 
 *   returns `true`. This function can include actions like logging or halting the system.
 * 
 * Example conditions include detecting specific reset reasons such as power-on, panic resets, 
 * or unknown resets.
 * 
 * @return std::vector<ESPRIC::ESPRIC_Condition> 
 *         A vector containing all the conditions to be checked by the analyzer.
 */
std::vector<ESPRIC::ESPRIC_Condition> getMyESPRIC_Conditions() {
  return {
    // Condition for an unknown reset reason
    {
      []() { return esp_reset_reason() == ESP_RST_UNKNOWN; }, // Condition
      []() { Serial.println("Memory reflashed? (Unknown reset reason)"); } // Callback
    },
     
    // Condition for a power-on reset
    {
      []() { return esp_reset_reason() == ESP_RST_POWERON; }, // Condition
      []() { Serial.println("Power-on detected."); } // Callback
    },
     
    // Condition for a panic reset
    {
      []() { return esp_reset_reason() == ESP_RST_PANIC; }, // Condition
      []() { 
        Serial.println("Panic reset detected. STOP!");
        while (1) {}; // Halt the program
      }
    },
  };
}

/**
 * @brief Sets up the ESP32 and starts the ESPRIC analyzer.
 * 
 * This function is executed once when the ESP32 starts. It initializes the serial 
 * interface for logging, displays a startup message, and runs the ESPRIC analyzer 
 * to evaluate the conditions defined in `getMyESPRIC_Conditions()`. 
 * 
 * The analyzer executes the callback functions for all matching conditions.
 */
void setup() {
  // Initialize serial interface for debugging and output
  Serial.begin(115200);
  while (!Serial) {};  // Wait for the serial interface to be ready (important for some ESP32 boards)
  Serial.println("Firmware started: ESPRIC - BasicUsage");

  // Create and initialize ESPRIC analyzer with the defined conditions
  ESPRIC analyzer(getMyESPRIC_Conditions());

  // Start the analyzer
  Serial.println("Start Analyzer...");
  analyzer.analyze();  // Analyze the reset conditions and execute callbacks
  Serial.println("Ready!");
}

/**
 * @brief Main program loop.
 * 
 * This function is called repeatedly after the `setup()` function has finished. 
 * In this example, it is left empty because the condition analysis is performed 
 * entirely in `setup()`.
 */
void loop() {
  // Main application logic goes here
  // In this example, nothing is done in the loop
}
