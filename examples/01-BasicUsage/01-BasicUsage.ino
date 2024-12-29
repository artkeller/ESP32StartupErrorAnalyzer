/**
* @file 01-BasicUsage.ino
* @brief Example of how to use the ESP32StartupErrorAnalyzer to analyse the cause of the reset.
* 
* This example shows how to use the ESP32StartupErrorAnalyzer to define reset conditions
* and register callback functions to process the corresponding conditions.
* The results are output via the serial interface.
*/

#include <ESP32StartupErrorAnalyzer.h>

/**
* @brief Defines the reset conditions and their associated callback functions.
* 
* This function creates a list of conditions for the analyser to check.
* Each condition consists of two lambda functions:
* - The first function returns a boolean value that indicates whether the condition is met.
* - The second function defines what should happen if the condition is met.
* 
* @return std::vector<ESP32StartupErrorAnalyzer::ErrorCondition> 
*         List of defined conditions.
*/
std::vector<ESP32StartupErrorAnalyzer::ErrorCondition> getRestartConditions() {
  return {
    // Unknown reset reason, e.g. after uploading a new sketch
    {[]() { return esp_reset_reason() == ESP_RST_UNKNOWN; }, []() { Serial.println("Reset reason could not be determined."); }},

    // Power-on reset, e.g. after pressing the RST button
    {[]() { return esp_reset_reason() == ESP_RST_POWERON; }, []() { Serial.println("Power-on event detected."); }},
  };
}

/**
* @brief Setup function that is called once when the ESP32 starts.
* 
* Initialises the serial interface, outputs a start message and starts
* the ESP32StartupErrorAnalyzer with the defined conditions.
*/
void setup() {
  // Initialise serial interface
  Serial.begin(115200);
  while (!Serial) {};  // Wait until serial connection is ready (ESP32C3...)
  Serial.println("Firmware started: ESP32StartupErrorAnalyzer - BasicUsage");

  // Start the analyser with defined conditions
  ESP32StartupErrorAnalyzer analyzer(getRestartConditions());

  Serial.println("Start Analyzer...");
  analyzer.analyze();  // Analyse conditions and execute corresponding callbacks
  Serial.println("Ready!");
}

/**
* @brief Main program loop that runs continuously.
* 
* In this example, the loop remains empty because the analysis of the conditions
* takes place exclusively in the `setup()` part.
*/
void loop() {
  // Main logic
}