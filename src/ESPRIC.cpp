/**
 * @file ESPRIC.cpp
 * @brief Implementation of the ESPRIC class.
 * 
 * This source file contains the implementation of methods for analyzing ESP32 startup 
 * conditions and executing associated callbacks. It now supports returning detailed results 
 * about matched and unmatched conditions.
 */

#include "ESPRIC.h"

/**
 * @brief Constructs the ESPRIC with predefined conditions and an optional default callback.
 * 
 * @param conditions A vector of `ESPRIC_Condition` structures to evaluate.
 * @param defaultCallback An optional callback executed if no conditions are met.
 * 
 * This constructor initializes the analyzer with a list of predefined conditions and 
 * optionally sets a default callback to handle cases where no conditions match.
 */
ESPRIC::ESPRIC(
    const std::vector<ESPRIC_Condition>& conditions,
    Callback defaultCallback)
    : conditions_(conditions), defaultCallback_(defaultCallback) {}

1/**
 * @brief Analyzes the defined conditions and executes the corresponding callbacks.
 * 
 * This method iterates through the list of defined conditions and executes the callback 
 * for each condition that evaluates to true. If no conditions are met and a default 
 * callback is defined, the default callback is executed. The method returns a struct 
 * containing the count of matched and unmatched conditions.
 * 
 * @return AnalysisResult Struct containing counts of matched and unmatched conditions.
 */
ESPRIC::AnalysisResult ESPRIC::analyze() {
    AnalysisResult result = {0, 0}; ///< Initialize result struct.

    for (const auto& condition : conditions_) {
        if (condition.condition()) {  // Check if the condition is true
            condition.callback();     // Execute the associated callback
            result.matched++;         // Increment matched count
        } else {
            result.unmatched++;       // Increment unmatched count
        }
    }

    // Execute the default callback if no conditions matched and it is defined
    if (result.matched == 0 && defaultCallback_) {
        defaultCallback_();
    }

    return result; ///< Return the analysis result.
}

/**
 * @brief Adds a new condition and its associated callback dynamically during runtime.
 * 
 * @param condition A condition function that evaluates to true or false.
 * @param callback A callback function to execute if the condition is true.
 * 
 * This method allows developers to add new conditions and their callbacks dynamically. 
 * The added conditions are evaluated during the next call to `analyze`.
 */
void ESPRIC::addCondition(const Condition& condition, const Callback& callback) {
    conditions_.push_back({condition, callback}); ///< Add the new condition and callback to the list.
}
