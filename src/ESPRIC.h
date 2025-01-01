/**
 * @file ESPRIC.h
 * @brief A utility class for analyzing and handling ESP32 startup conditions.
 * 
 * This header defines the `ESPRIC` class, which allows developers to analyze 
 * the startup state of an ESP32 device and execute specific callbacks based on detected conditions. 
 * The class supports both predefined and dynamically added conditions, with optional default callbacks.
 */

#ifndef ESPRIC_H
#define ESPRIC_H

#ifdef ESP32

#include <functional>
#include <vector>

/**
 * @class ESPRIC
 * @brief A class for analyzing ESP32 startup conditions and executing corresponding callbacks.
 * 
 * This class is designed to evaluate a set of conditions defined as lambda functions and 
 * execute associated callbacks when the conditions are met. It also allows dynamic addition of 
 * new conditions during runtime.
 */
class ESPRIC {
public:
    /**
     * @brief Type alias for condition logic.
     * 
     * The `Condition` type represents a boolean function that evaluates whether a specific 
     * startup condition is met.
     */
    using Condition = std::function<bool()>;

    /**
     * @brief Type alias for callback logic.
     * 
     * The `Callback` type represents a function that executes the desired logic when a 
     * condition is met.
     */
    using Callback = std::function<void()>;

    /**
     * @struct ESPRIC_Condition
     * @brief Represents a pairing of a condition and its associated callback.
     * 
     * The `ESPRIC_Condition` structure associates a specific `Condition` with a `Callback` 
     * that is executed when the condition is true.
     */
    struct ESPRIC_Condition {
        Condition condition;  ///< The condition to evaluate.
        Callback callback;    ///< The callback to execute if the condition is true.
    };

    /**
     * @struct AnalysisResult
     * @brief Represents the result of analyzing conditions.
     * 
     * This structure contains the number of matched and unmatched conditions, allowing the 
     * caller to understand the outcome of the analysis.
     */
    struct AnalysisResult {
        size_t matched;    ///< Number of conditions that were met.
        size_t unmatched;  ///< Number of conditions that were not met.
    };

    /**
     * @brief Constructor to initialize the analyzer with predefined conditions.
     * 
     * @param conditions A vector of predefined `ESPRIC_Condition` structures to evaluate.
     * @param defaultCallback (Optional) A default callback to execute if no conditions are met.
     * 
     * The constructor initializes the analyzer with a set of predefined conditions 
     * and an optional default callback. If no conditions are met during analysis, the 
     * default callback is executed.
     */
    ESPRIC(const std::vector<ESPRIC_Condition>& conditions, Callback defaultCallback = nullptr);

    /**
     * @brief Analyzes the conditions and executes the corresponding callbacks.
     * 
     * This method evaluates all defined conditions in order and executes the associated 
     * callback for each condition that evaluates to true. If no conditions are met 
     * and a default callback is defined, the default callback is executed.
     * 
     * @return An `AnalysisResult` structure containing the counts of matched and unmatched conditions.
     */
    AnalysisResult analyze();

    /**
     * @brief Adds a new condition and its callback dynamically during runtime.
     * 
     * @param condition The condition logic to evaluate.
     * @param callback The callback to execute if the condition is true.
     * 
     * This method allows the dynamic addition of new conditions and their callbacks, 
     * enabling flexibility in defining startup analysis logic.
     */
    void addCondition(const Condition& condition, const Callback& callback);

private:
    std::vector<ESPRIC_Condition> conditions_; ///< List of all defined startup conditions.
    Callback defaultCallback_;                ///< Optional default callback if no conditions are met.
};

#else

#warning "The ESPRIC library is specifically designed for ESP32 devices and relies on ESP-IDF reset and \
wakeup cause APIs. Currently, no other MCU platform provides equivalent post-mortem analysis capabilities. \
Please use this library with ESP32-compatible devices only."

#error "For generic ANY Reboot Investigation and Context Integrity Check see for the ANYRIC project on github"

#endif // ESP32

#endif // ESPRIC_H
