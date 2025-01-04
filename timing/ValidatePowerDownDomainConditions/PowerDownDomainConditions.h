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
