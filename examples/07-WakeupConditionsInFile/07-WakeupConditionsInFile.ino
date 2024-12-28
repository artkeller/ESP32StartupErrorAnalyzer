/**
 * @file 02-WakeupConditionsInFile.ino
 * @brief Example demonstrating the usage of ESP32StartupErrorAnalyzer with conditions defined in a separate file.
 * 
 * This example shows how to separate the definition of startup conditions and callbacks 
 * into an external file for better modularity and reusability. The `StartupConditions.h` file 
 * contains the conditions to be analyzed by the ESP32StartupErrorAnalyzer.
 */

#include <ESP32StartupErrorAnalyzer.h>
#include "RestartConditions.h"

const uint32_t SLEEP_DURATION_US = 10 * 1000000; // 10 Sekunden

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

  if (wakeupCounter == 0) {
    Serial.println("-> Führe harten Reset durch...");
    delay(3000); // allow pause
    esp_restart();
  } else {
    // In den Tiefschlaf gehen
    Serial.printf("-> Geh in den Tiefschlaf für %d Sekunden...\n", SLEEP_DURATION_US / 1000000);
    esp_sleep_enable_timer_wakeup(SLEEP_DURATION_US);
    esp_deep_sleep_start();
  }
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
