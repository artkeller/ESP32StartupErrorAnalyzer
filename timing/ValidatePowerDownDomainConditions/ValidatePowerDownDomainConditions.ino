/**
 * @file ValidatePowerDownDomainConditions.ino
 * @brief Sketch to validate ESP32 powerdown domain conditions and log detailed test reports.
 *
 * This sketch uses the `PowerDownDomainConditions.h` header to define and test
 * various power domain configurations in ESP32 deep sleep mode. It provides
 * detailed logging for both successful and failed configurations.
 */

#include <vector>
#include "PowerDownDomainConditions.h"  // Include power domain conditions from the header file

/**
 * @brief Helper function to evaluate errors in ESP-IDF function calls.
 *
 * This function checks the return value of an ESP-IDF function call and logs an error
 * if the return value indicates failure. It is used to assess the success of power domain configurations.
 * 
 * @param err The return value of an ESP-IDF function5 call.
 * @param domainName A string representing the powerdown domain being configured.
 * @return True if an error occurred, otherwise false.
 */
bool isError(esp_err_t err, const char* domainName) {
  //err = 0xffff; // Test Error condtion
  if (err != ESP_OK) {
    log_e("Configuration failed for %s: Error code: 0x%X", domainName, err);
    return true;
  }
  return false;
}

/**
 * @brief Tests powerdown domain conditions and logs a detailed report.
 *
 * This function iterates through a vector of `PowerDownDomainCondition` objects,
 * evaluates each condition, and logs the results. If a condition fails, the
 * associated error callback is executed.
 *
 * @param conditions A vector of `PowerDownDomainCondition` objects representing the powerdown domains to be tested.
 */
void testPowerDownDomainConditions(const std::vector<PowerDownDomainCondition>& conditions) {
  bool allConditionsPassed = true;
  log_i("Starting 'PowerDownDomainConditions' Test Report:\n");

  // Iterate through all conditions and test them
  for (size_t i = 0; i < conditions.size(); ++i) {
    log_d("Testing Condition %zu: %s", i + 1, conditions[i].conditionName);

    // Test the condition
    bool conditionResult = conditions[i].condition();

    // Log the result
    if (conditionResult) {
      log_e("Condition '%s' failed.", conditions[i].conditionName);
      allConditionsPassed = false;

      // Execute the error callback
      conditions[i].callback();
    } else {
      log_d("Condition '%s' passed.\n", conditions[i].conditionName);
    }
  }

  // Summary of test results
  if (allConditionsPassed) {
    log_i("All conditions passed.");
  } else {
    log_w("Some conditions failed.");
  }
}

/**
 * @brief Sets up the test environment and runs the power domain conditions test.
 *
 * This function initializes the serial communication, retrieves the power domain
 * conditions from the header file, and executes the test.
 */
void setup() {
  Serial.begin(115200);
  delay(1000);  // Wait for Serial monitor to initialize
  while (!Serial) {}

  // Retrieve the conditions defined in the header file
  auto conditions = definePowerDownDomainConditions();

  // Execute the test
  testPowerDownDomainConditions(conditions);
}

/**
 * @brief Main loop of the sketch.
 *
 * This loop remains empty as the focus of the sketch is the one-time test
 * executed in the `setup` function.
 */
void loop() {
  // Main loop remains empty as this sketch focuses solely on the test.
}
