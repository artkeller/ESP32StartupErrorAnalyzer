#include <ESP32StartupErrorAnalyzer.h>

// Bedingungen und Callbacks definieren
std::vector<ESP32StartupErrorAnalyzer::ErrorCondition> getStartupConditions() {
    return {
        {[]() { return esp_reset_reason() == ESP_RST_PANIC; }, []() { Serial.println("Panik-Reset erkannt."); }},
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0; }, []() { Serial.println("Wakeup durch externes Signal."); }}
    };
}

void setup() {
    Serial.begin(115200);

    ESP32StartupErrorAnalyzer analyzer(getStartupConditions());
    analyzer.analyze();
}

void loop() {
    // Hauptlogik
}
