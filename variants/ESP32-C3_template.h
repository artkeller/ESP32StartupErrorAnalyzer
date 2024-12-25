/**
 * @file ESP32_C3_Template.h
 * @brief Definiert spezifische Reset- und Wakeup-Ursachen für den ESP32-C3.
 *
 * Dieses Template enthält eine Liste von Fehlerbedingungen und zugehörigen Handlungen, 
 * die spezifisch für den ESP32-C3 sind. Es bietet eine Möglichkeit, die Reset-Ursachen 
 * sowie die Wakeup-Ursachen zu analysieren und entsprechende Diagnosen auszugeben.
 *
 * @details Jede Fehlerbedingung wird als Lambda-Funktion definiert, die den entsprechenden 
 * Zustand überprüft und eine Diagnosenachricht ausgibt, falls die Bedingung erfüllt ist.
 *
 * @note Dieses Template basiert auf der ESP-IDF API und verwendet die Klasse 
 *       `ESP32StartupErrorAnalyzer`.
 */

#ifndef ESP32_C3_TEMPLATE_H
#define ESP32_C3_TEMPLATE_H

#include <ESP32StartupErrorAnalyzer.h>

/**
 * @brief Liefert die spezifischen Startup-Bedingungen für den ESP32-C3.
 * 
 * Diese Funktion definiert eine Liste von Fehlerbedingungen, die während des 
 * Startvorgangs auftreten können. Jede Bedingung besteht aus zwei Lambda-Funktionen:
 * - Eine, die den Zustand überprüft.
 * - Eine, die eine Diagnosenachricht ausgibt, falls die Bedingung erfüllt ist.
 *
 * @return std::vector<ESP32StartupErrorAnalyzer::ErrorCondition> 
 *         Eine Liste der definierten Fehlerbedingungen.
 *
 * @code{.cpp}
 * auto conditions = getStartupConditions();
 * for (const auto& condition : conditions) {
 *     if (condition.check()) {
 *         condition.action();
 *     }
 * }
 * @endcode
 */
std::vector<ESP32StartupErrorAnalyzer::ErrorCondition> getStartupConditions() {
    return {
        /**
         * @brief Power-On Reset Bedingung (ESP32-C3).
         *
         * Diese Bedingung überprüft, ob der ESP32-C3 durch ein Power-On-Ereignis 
         * zurückgesetzt wurde, und gibt eine entsprechende Nachricht aus.
         */
        {[]() { return esp_reset_reason() == ESP_RST_POWERON; },
         []() { Serial.println("Power-On reset detected!"); }},
        
        /**
         * @brief Software Reset Bedingung (ESP32-C3).
         *
         * Diese Bedingung überprüft, ob der ESP32-C3 durch einen Software-Reset 
         * (z. B. `esp_restart`) zurückgesetzt wurde.
         */
        {[]() { return esp_reset_reason() == ESP_RST_SW; },
         []() { Serial.println("Software reset detected!"); }},
        
        /**
         * @brief Panic Reset Bedingung (ESP32-C3).
         *
         * Diese Bedingung überprüft, ob der ESP32-C3 aufgrund eines Panic-Resets 
         * (z. B. durch eine Ausnahme) zurückgesetzt wurde.
         */
        {[]() { return esp_reset_reason() == ESP_RST_PANIC; },
         []() { Serial.println("Panic reset detected!"); }},
        
        /**
         * @brief Wakeup durch externes Signal (EXT0) (ESP32-C3).
         *
         * Diese Bedingung überprüft, ob der ESP32-C3 durch ein externes Signal 
         * aufgewacht ist.
         */
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0; },
         []() { Serial.println("Wake-up by external signal!"); }},
        
        /**
         * @brief Wakeup durch GPIO-Interrupt (ESP32-C3).
         *
         * Diese Bedingung überprüft, ob der ESP32-C3 durch einen GPIO-Interrupt 
         * aufgewacht ist.
         */
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_GPIO; },
         []() { Serial.println("Wake-up by GPIO!"); }},
        
        /**
         * @brief Wakeup durch Timer (ESP32-C3).
         *
         * Diese Bedingung überprüft, ob der ESP32-C3 durch einen Timer 
         * aufgewacht ist.
         */
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER; },
         []() { Serial.println("Wake-up by timer!"); }}
    };
}

#endif // ESP32_C3_TEMPLATE_H
