#include <ESP32StartupErrorAnalyzer.h>
#include "StartupConditions.h"

void setup() {
    Serial.begin(115200);

    ESP32StartupErrorAnalyzer analyzer(getStartupConditions());

    // Zusätzliche Bedingungen dynamisch hinzufügen
    analyzer.addCondition(
        []() { return esp_reset_reason() == ESP_RST_DEEPSLEEP; },
        []() { Serial.println("Deep-Sleep-Reset erkannt."); }
    );

    analyzer.addCondition(
        []() { return esp_reset_reason() == ESP_RST_SW; },
        []() { Serial.println("Software-Reset erkannt."); }
    );

    analyzer.analyze();
}

void loop() {
    // Hauptlogik
}
