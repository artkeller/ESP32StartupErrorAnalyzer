#include <ESP32StartupErrorAnalyzer.h>
#include "StartupConditions.h"

void setup() {
    Serial.begin(115200);

    ESP32StartupErrorAnalyzer analyzer(getStartupConditions());
    analyzer.analyze();
}

void loop() {
    // Hauptlogik
}
