/**
 * @file 10_ResetWakeupDemo.ino
 * @brief Demonstrates the use of the ESPRIC library to analyze ESP32 reset and wakeup causes.
 * 
 * This example uses two independent `ESPRIC` objects to analyze the causes of resets and wakeups.
 * The analysis is done using predefined conditions for both reset and wakeup causes, as defined
 * in the `ESPRIC_Conditions.h` header file.
 * 
 * @note This example requires the ESPRIC library and is tested with the ESP32 series.
 *       Some reset codes, such as USB reset or power glitch reset, are only available 
 *       on newer ESP32 chips (e.g., ESP32-S2, ESP32-S3). Ensure compatibility before use.
 * 
 * @author Thomas Walloschke <artkeller@gmc.de>
 * @date 20250101
 */

#include <ESPRIC.h>
#include "ESPRIC_Conditions.h"

void setup() {
    // Initialize the serial communication for debugging.
    Serial.begin(115200);
    delay(1000);

    Serial.println("\n=== ESP Reset and Wakeup Cause Analysis with ESPRIC ===");

    // Create two independent ESPRIC objects for reset and wakeup analysis.
    ESPRIC resetAnalyzer(getResetConditions());
    ESPRIC wakeupAnalyzer(getWakeupConditions());

    // Analyze reset causes.
    Serial.println("\nAnalyzing Reset Causes:");
    resetAnalyzer.analyze();

    // Analyze wakeup causes.
    Serial.println("\nAnalyzing Wakeup Causes:");
    wakeupAnalyzer.analyze();
}

void loop() {
    // No additional logic required in this example.
    delay(5000);
}
