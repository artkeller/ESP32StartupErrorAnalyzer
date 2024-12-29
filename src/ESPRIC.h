/**
 * @file ESPRIC.h
 * @brief A utility class for analyzing and handling ESP32 startup conditions.
 * 
 * This header defines the `ESPRIC` class, which allows developers to analyze 
 * the startup state of an ESP32 device and execute specific callbacks based on detected conditions. 
 * The class supports both predefined and dynamically added conditions, with optional default callbacks.

 New name candidatea: 
 
    ESPRIC: ESP32 Reboot Investigation and Context Integrity Check - highscore *****
    ESRACS: ESP32 State Recovery And Context Safety - ***
    ESPRAR: ESP32 Restart Analyzer - ***
    ESPRAS: ESP32 Restart and State Analyzer - ****

 */

#ifndef ESPRIC_H
#define ESPRIC_H

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
     * @struct ErrorCondition
     * @brief Represents a pairing of a condition and its associated callback.
     * 
     * The `ErrorCondition` structure associates a specific `Condition` with a `Callback` 
     * that is executed when the condition is true.
     */
    struct ErrorCondition {
        Condition condition;  ///< The condition to evaluate.
        Callback callback;    ///< The callback to execute if the condition is true.
    };

    /**
     * @brief Constructor to initialize the error analyzer with predefined conditions.
     * 
     * @param conditions A vector of predefined `ErrorCondition` structures to evaluate.
     * @param defaultCallback (Optional) A default callback to execute if no conditions are met.
     * 
     * The constructor initializes the error analyzer with a set of predefined conditions 
     * and an optional default callback. If no conditions are met during analysis, the 
     * default callback is executed.
     */
    ESPRIC(const std::vector<ErrorCondition>& conditions, Callback defaultCallback = nullptr);

    /**
     * @brief Analyzes the conditions and executes the corresponding callbacks.
     * 
     * This method evaluates all defined conditions in order and executes the associated 
     * callback for the first condition that evaluates to true. If no conditions are met 
     * and a default callback is defined, the default callback is executed.
     */
    void analyze();

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
    std::vector<ErrorCondition> conditions_; ///< List of all defined error conditions.
    Callback defaultCallback_;              ///< Optional default callback if no conditions are met.
};

#endif // ESPRIC_H
