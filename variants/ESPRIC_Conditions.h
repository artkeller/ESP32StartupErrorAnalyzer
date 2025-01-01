/**
 * @file ESPRIC_Conditions.h
 * @brief Defines conditions for ESP32 reset and wakeup causes.
 *
 * @author Artkeller <artkeller@gmx-de>
 * @date 20250101
 *
 * This header provides a set of conditions for analyzing the reset and wakeup
 * causes of an ESP32 device using the ESPRIC library. It covers all documented
 * reset and wakeup causes, allowing developers to handle specific scenarios
 * programmatically.
 */

#ifndef ESPRIC_CONDITIONS_H
#define ESPRIC_CONDITIONS_H

#include <ESPRIC.h>

/**
 * @brief Get predefined reset conditions for the ESP32.
 * 
 * This function defines a vector of conditions for various ESP_RST causes.
 * Each condition includes a detection function and an associated callback.
 * 
 * @return A vector of `ESPRIC_Condition` objects for reset analysis.
 */
std::vector<ESPRIC_Condition> getResetConditions() {
    return {
        {[]() { return esp_reset_reason() == ESP_RST_UNKNOWN; }, 
         []() { Serial.println("Unknown reset detected."); }},
        {[]() { return esp_reset_reason() == ESP_RST_POWERON; }, 
         []() { Serial.println("Power-on reset detected."); }},
        {[]() { return esp_reset_reason() == ESP_RST_EXT; }, 
         []() { Serial.println("External signal reset detected."); }},
        {[]() { return esp_reset_reason() == ESP_RST_SW; }, 
         []() { Serial.println("Software reset detected."); }},
        {[]() { return esp_reset_reason() == ESP_RST_PANIC; }, 
         []() { Serial.println("Panic reset detected."); }},
        {[]() { return esp_reset_reason() == ESP_RST_INT_WDT; }, 
         []() { Serial.println("Interrupt watchdog reset detected."); }},
        {[]() { return esp_reset_reason() == ESP_RST_TASK_WDT; }, 
         []() { Serial.println("Task watchdog reset detected."); }},
        {[]() { return esp_reset_reason() == ESP_RST_WDT; }, 
         []() { Serial.println("General watchdog reset detected."); }},
        {[]() { return esp_reset_reason() == ESP_RST_DEEPSLEEP; }, 
         []() { Serial.println("Deep sleep wake-up reset detected."); }},
        {[]() { return esp_reset_reason() == ESP_RST_BROWNOUT; }, 
         []() { Serial.println("Brownout reset detected."); }},
        {[]() { return esp_reset_reason() == ESP_RST_SDIO; }, 
         []() { Serial.println("SDIO reset detected."); }},
        {[]() { return esp_reset_reason() == ESP_RST_USB; }, 
         []() { Serial.println("USB reset detected."); }},
        {[]() { return esp_reset_reason() == ESP_RST_JTAG; }, 
         []() { Serial.println("JTAG reset detected."); }},
        {[]() { return esp_reset_reason() == ESP_RST_EFUSE; }, 
         []() { Serial.println("eFuse reset detected."); }},
        {[]() { return esp_reset_reason() == ESP_RST_PWR_GLITCH; }, 
         []() { Serial.println("Power glitch reset detected."); }},
        {[]() { return esp_reset_reason() == ESP_RST_CPU_LOCKUP; }, 
         []() { Serial.println("CPU lockup reset detected."); }}
    };
}

/**
 * @brief Get predefined wakeup conditions for the ESP32.
 * 
 * This function defines a vector of conditions for various wakeup causes.
 * Each condition includes a detection function and an associated callback.
 * 
 * @return A vector of `ESPRIC_Condition` objects for wakeup analysis.
 */
std::vector<ESPRIC_Condition> getWakeupConditions() {
    return {
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_UNDEFINED; }, 
         []() { Serial.println("No defined wakeup cause."); }},
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0; }, 
         []() { Serial.println("Wakeup caused by external signal via RTC_IO."); }},
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT1; }, 
         []() { Serial.println("Wakeup caused by external signal via RTC_CNTL."); }},
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER; }, 
         []() { Serial.println("Wakeup caused by timer."); }},
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TOUCHPAD; }, 
         []() { Serial.println("Wakeup caused by touchpad interrupt."); }},
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_ULP; }, 
         []() { Serial.println("Wakeup caused by ULP program."); }},
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_GPIO; }, 
         []() { Serial.println("Wakeup caused by GPIO (light sleep only)."); }},
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_UART; }, 
         []() { Serial.println("Wakeup caused by UART (light sleep only)."); }},
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_WIFI; }, 
         []() { Serial.println("Wakeup caused by WiFi (light sleep only)."); }},
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_COCPU; }, 
         []() { Serial.println("Wakeup caused by co-processor interrupt."); }},
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG; }, 
         []() { Serial.println("Wakeup caused by co-processor crash."); }},
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_BT; }, 
         []() { Serial.println("Wakeup caused by Bluetooth (light sleep only)."); }}
    };
}

#endif // ESPRIC_CONDITIONS_H
