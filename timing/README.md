* Timing

der folgende sketch prüft PowerDownDomainConditions.h

ValidatePowerDownDomainConditions.ino
```cpp
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
```

PowerDownDomainConditions.h
```cpp
/**
 * @file PowerDownDomainConditions.h
 * @brief Defines power domain conditions and their respective error handling callbacks for ESP32 deep sleep mode.
 *
 * This header file allows defining and configuring various power domains in ESP32's deep sleep mode.
 * Each power domain is associated with a condition-checking function and an error callback
 * that is executed if the condition fails.
 */

#include "hal/esp_flash_err.h"
#ifndef POWERDOWNDOMAINCONDITIONS_H
#define POWERDOWNDOMAINCONDITIONS_H

#include <functional>
#include <vector>
#include <esp_sleep.h>  // Required for esp_sleep_pd_config function

/**
 * @brief Checks for errors in ESP-IDF API calls and logs the error message.
 * 
 * This function evaluates the return value of ESP-IDF functions, determines if an error occurred,
 * and logs the domain name associated with the error.
 * 
 * @param err The return value of the ESP-IDF function to evaluate.
 * @param domainName A string representing the power domain being configured.
 * @return True if an error occurred, otherwise false.
 */
bool isError(esp_err_t err, const char* domainName);

/**
 * @struct PowerDownDomainCondition
 * @brief Represents 3a condition and its associated error callback for powerdown domain configuration.
 * 
 * This structure contains the name of the powerdown domain, a lambda function to test the configuration 
 * condition, and a lambda function that is invoked if the configuration fails.
 */
struct PowerDownDomainCondition {
  const char* conditionName;                 /**< Name of the powerdown domain for logging and debugging. */
  std::function<bool()> condition;          /**< Lambda function to test the condition. */
  std::function<void()> callback;           /**< Lambda function invoked on failure. */
};

/**
 * @brief Defines power domain configuration conditions and their respective error callbacks.
 * 
 * This function creates a list of conditions for configuring ESP32 power domains during deep sleep.
 * Each condition verifies the success of an `esp_sleep_pd_config` call and defines a specific
 * error-handling callback.
 * 
 * @note Some power domains, such as the CPU domain, are included conditionally based on 
 *       the SOC's capabilities (`SOC_PM_SUPPORT_CPU_PD`).
 * 
 * @return A vector of `PowerDomainCondition` structures, each representing a power domain.
 */
std::vector<PowerDownDomainCondition> definePowerDownDomainConditions() {
  return {
    {
      "RTC8M PD Domain", 
      []() { return isError(esp_sleep_pd_config(ESP_PD_DOMAIN_RTC8M, ESP_PD_OPTION_OFF), "RTC8M"); },
      []() { log_e("Failed to configure 'RTC8M' powerdown domain."); }
    },
    {
      "RTC_FAST_MEM PD Domain", 
      []() { return isError(esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_ON), "RTC_FAST_MEM"); },
      []() { log_e("Failed to configure 'RTC_FAST_MEM' powerdown domain."); }
    },
    {
      "RTC_SLOW_MEM PD Domain", 
      []() { return isError(esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_ON), "RTC_SLOW_MEM"); },
      []() { log_e("Failed to configure 'RTC_SLOW_MEM' powerdown domain."); }
    },
    {
      "RTC_PERIPH PD Domain", 
      []() { return isError(esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF), "RTC_PERIPH"); },
      []() { log_e("Failed to configure 'RTC_PERIPH' powerdown domain."); }
    },
    {
      "XTAL PD Domain", 
      []() { return isError(esp_sleep_pd_config(ESP_PD_DOMAIN_XTAL, ESP_PD_OPTION_OFF), "XTAL"); },
      []() { log_e("Failed to configure 'XTAL' powerdown domain."); }
    },
#if SOC_PM_SUPPORT_CPU_PD
    {
      "CPU PD Domain", 
      []() { return isError(esp_sleep_pd_config(ESP_PD_DOMAIN_CPU, ESP_PD_OPTION_OFF), "CPU"); },
      []() { log_e("Failed to configure 'CPU' domain."); }
    },
#endif
    {
      "VDDSDIO PD Domain", 
      []() { return isError(esp_sleep_pd_config(ESP_PD_DOMAIN_VDDSDIO, ESP_PD_OPTION_OFF), "VDDSDIO"); },
      []() { log_e("Failed to configure 'VDDSDIO' domain."); }
    }
  };
}

#endif // POWERDOWNDOMAINCONDITIONS_H
```

 mit Debug Level "Info" compiliert wird folgendes gelogged:

```kog
    00:07:58.508 -> [  1044][I][ValidatePowerDownDomainConditions.ino:43] testPowerDownDomainConditions(): Starting 'PowerDownDomainConditions' Test Report:
    00:07:58.508 -> 
    00:07:58.508 -> [  1046][I][ValidatePowerDownDomainConditions.ino:66] testPowerDownDomainConditions(): All conditions passed.
```