/**
 * @file 02-ModularESPRICExample.ino
 * @brief Example showcasing how to use ESPRIC in a modular way with restart conditions defined externally.
 * 
 * This sketch demonstrates how to encapsulate ESP32 restart conditions and their callbacks
 * in a reusable header file, keeping the main sketch lightweight and focused.
 */

#include <ESPRIC.h>
#include "RestartConditions.h"

/**
 * @brief Initializes the firmware and runs the ESPRIC analyzer with predefined restart conditions.
 * 
 * This function:
 * - Sets up the serial communication for debugging.
 * - Creates an instance of ESPRIC with the conditions defined in `RestartConditions.h`.
 * - Executes the analysis during the setup phase.
 */
void setup() {
  // Initialize the serial interface
  Serial.begin(115200);
  while (!Serial) {};  // Wait until the serial connection is ready
  Serial.println("Firmware started: ESPRIC - Modular Example");

  // Instantiate and run the analyzer
  ESPRIC analyzer(getRestartConditions());

  Serial.println("Starting Analyzer...");
  analyzer.analyze();  // Perform analysis and execute callbacks
  Serial.println("Analyzer Complete!");
}

/**
 * @brief Main loop function.
 * 
 * No additional logic is implemented in this example as the analysis is handled in `setup()`.
 */
void loop() {
  // Additional runtime logic could be added here
}
