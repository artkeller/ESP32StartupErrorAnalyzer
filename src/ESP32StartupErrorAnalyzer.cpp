#include "ESP32StartupErrorAnalyzer.h"

// Konstruktor
StartupErrorAnalyzer::StartupErrorAnalyzer(const std::vector<ErrorCondition>& conditions, Callback defaultCallback)
    : conditions_(conditions), defaultCallback_(defaultCallback) {}

// Führe die Analyse durch
void StartupErrorAnalyzer::analyze() {
    bool conditionMatched = false;
    for (const auto& condition : conditions_) {
        if (condition.condition()) {
            condition.callback();
            conditionMatched = true;
        }
    }

    // Falls keine Bedingungen erfüllt sind, führe das Default-Callback aus (falls definiert)
    if (!conditionMatched && defaultCallback_) {
        defaultCallback_();
    }
}

// Dynamisches Hinzufügen weiterer Bedingungen
void StartupErrorAnalyzer::addCondition(const Condition& condition, const Callback& callback) {
    conditions_.push_back({condition, callback});
}
