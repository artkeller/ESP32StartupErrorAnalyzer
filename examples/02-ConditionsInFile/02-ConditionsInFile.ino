/**
 * @file 02-ConditionsInFile.ino
 * @brief Example demonstrating the usage of ESP32StartupErrorAnalyzer with conditions defined in a separate file.
 * 
 * This example shows how to separate the definition of startup conditions and callbacks 
 * into an external file for better modularity and reusability. The `StartupConditions.h` file 
 * contains the conditions to be analyzed by the ESP32StartupErrorAnalyzer.
 */

#include <ESP32StartupErrorAnalyzer.h>
#include "StartupConditions.h"

/**
 * @brief Initializes the firmware, configures the analyzer, and performs startup condition analysis.
 * 
 * This function:
 * - Initializes the serial connection.
 * - Instantiates the ESP32StartupErrorAnalyzer with conditions defined in `StartupConditions.h`.
 * - Performs the analysis and executes the corresponding callbacks for each matched condition.
 */
void setup() {
  // Initialize the serial connection
  Serial.begin(115200);
  while (!Serial) {};  // Wait until the serial connection is ready (important for some devices like ESP32-C3)
  Serial.println("Firmware started: ESP32StartupErrorAnalyzer - ConditionsInFile");

  // Create an instance of the analyzer and pass the defined conditions
  ESP32StartupErrorAnalyzer analyzer(getStartupConditions());

  Serial.println("Start Analyzer...");
  analyzer.analyze();  // Analyze the startup conditions and execute callbacks
  Serial.println("Ready!");
}

/**
 * @brief Main loop function.
 * 
 * This function is executed continuously after `setup()`. 
 * In this example, it is left empty because the analysis occurs entirely during the setup phase.
 */
void loop() {
  // Main logic can be added here
}
