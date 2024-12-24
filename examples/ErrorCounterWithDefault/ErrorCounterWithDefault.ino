#include <ESP32StartupErrorAnalyzer.h>

// RTC-Speicher für Fehlerzähler
RTC_DATA_ATTR int panicResetCounter = 0;
RTC_DATA_ATTR int powerOnResetCounter = 0;
RTC_DATA_ATTR int unknownResetCounter = 0;

std::vector<ESP32StartupErrorAnalyzer::ErrorCondition> getStartupConditions() {
    return {
        // Panik-Reset-Zähler erhöhen und melden
        {[]() { return esp_reset_reason() == ESP_RST_PANIC; },
         []() {
             panicResetCounter++;
             Serial.printf("Panik-Reset erkannt! Zähler: %d\n", panicResetCounter);
         }},
        // Power-On-Reset-Zähler erhöhen und melden
        {[]() { return esp_reset_reason() == ESP_RST_POWERON; },
         []() {
             powerOnResetCounter++;
             Serial.printf("Power-On erkannt! Zähler: %d\n", powerOnResetCounter);
         }},
        // Externes Wakeup
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0; },
         []() { Serial.println("Wakeup durch externes Signal."); }}
    };
}

void setup() {
    Serial.begin(115200);

    ESP32StartupErrorAnalyzer analyzer(getStartupConditions(),
                                      []() { // Default-Callback: Wenn keine Bedingungen erfüllt sind
                                          unknownResetCounter++;
                                          Serial.printf("Unbekannter Fehler! Zähler: %d\n", unknownResetCounter);
                                      });

    // Fehlerzähler bei bestimmten Bedingungen zurücksetzen
    analyzer.addCondition(
        []() { return esp_reset_reason() == ESP_RST_BROWNOUT; },
        []() {
            panicResetCounter = 0;
            powerOnResetCounter = 0;
            unknownResetCounter = 0;
            Serial.println("Brownout erkannt! Alle Fehlerzähler zurückgesetzt.");
        }
    );

    // Fehleranalyse durchführen
    analyzer.analyze();
}

void loop() {
    // Hauptlogik
}
