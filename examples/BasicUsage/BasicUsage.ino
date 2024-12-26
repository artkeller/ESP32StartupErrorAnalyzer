#include <ESP32StartupErrorAnalyzer.h>

// Bedingungen und Callbacks definieren
std::vector<ESP32StartupErrorAnalyzer::ErrorCondition> getStartupConditions() {
    return {
        {[]() { return esp_reset_reason() == ESP_RST_UNKNOWN; }, []() { Serial.println("Reset-Ursache konnte nicht bestimmt werden."); }},
        {[]() { return esp_reset_reason() == ESP_RST_POWERON; }, []() { Serial.println("Power-On-Ereignis erkannt."); }},
    };
} 

void setup() {
    Serial.begin(115200);
    while(!Serial) {};
    Serial.println("Firmware started: ESP32StartupErrorAnalyzer - BasicUsage");

    ESP32StartupErrorAnalyzer analyzer(getStartupConditions());

    Serial.println("Start Analyzer...");
    analyzer.analyze();
    Serial.println("Ready!");
}

void loop() {
    // Hauptlogik 
}
