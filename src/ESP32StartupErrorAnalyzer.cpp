#include "ESP32StartupErrorAnalyzer.h"

ESP32StartupErrorAnalyzer::ESP32StartupErrorAnalyzer(const std::vector<ErrorCondition>& conditions, Callback defaultCallback)
    : conditions_(conditions), defaultCallback_(defaultCallback) {}

void ESP32StartupErrorAnalyzer::analyze() {
    bool conditionMatched = false;
    for (const auto& condition : conditions_) {
        if (condition.condition()) {
            condition.callback();
            conditionMatched = true;
        }
    }

    if (!conditionMatched && defaultCallback_) {
        defaultCallback_();
    }
}

void ESP32StartupErrorAnalyzer::addCondition(const Condition& condition, const Callback& callback) {
    conditions_.push_back({condition, callback});
}
