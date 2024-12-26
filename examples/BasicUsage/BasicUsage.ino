/**
 * @file BasicUsage.ino
 * @brief Beispiel zur Nutzung des ESP32StartupErrorAnalyzer, um die Reset-Ursache zu analysieren.
 * 
 * Dieses Beispiel zeigt, wie man mit dem ESP32StartupErrorAnalyzer Reset-Bedingungen
 * definiert und Callback-Funktionen zur Verarbeitung der entsprechenden Bedingungen
 * registriert. Die Ergebnisse werden über die serielle Schnittstelle ausgegeben.
 */

#include <ESP32StartupErrorAnalyzer.h>

/**
 * @brief Definiert die Reset-Bedingungen und deren zugehörige Callback-Funktionen.
 * 
 * Diese Funktion erstellt eine Liste von Bedingungen, die der Analyzer prüfen soll.
 * Jede Bedingung besteht aus zwei Lambda-Funktionen:
 * - Die erste Funktion gibt einen booleschen Wert zurück, der angibt, ob die Bedingung erfüllt ist.
 * - Die zweite Funktion definiert, was passieren soll, wenn die Bedingung erfüllt ist.
 * 
 * @return std::vector<ESP32StartupErrorAnalyzer::ErrorCondition> 
 *         Liste der definierten Bedingungen.
 */
std::vector<ESP32StartupErrorAnalyzer::ErrorCondition> getStartupConditions() {
    return {
        // Unbekannte Reset-Ursache, z. B. nach Upload eines neuen Sketches
        {[]() { return esp_reset_reason() == ESP_RST_UNKNOWN; }, 
         []() { Serial.println("Reset-Ursache konnte nicht bestimmt werden."); }},
        
        // Power-On-Reset, z. B. nach Drücken des RST-Buttons
        {[]() { return esp_reset_reason() == ESP_RST_POWERON; }, 
         []() { Serial.println("Power-On-Ereignis erkannt."); }},
    };
}

/**
 * @brief Setup-Funktion, die einmalig beim Start des ESP32 aufgerufen wird.
 * 
 * Initialisiert die serielle Schnittstelle, gibt eine Startmeldung aus und startet
 * den ESP32StartupErrorAnalyzer mit den definierten Bedingungen.
 */
void setup() {
    // Serielle Schnittstelle initialisieren
    Serial.begin(115200);
    while(!Serial) {};  // Warten, bis die serielle Verbindung bereit ist (ESP32C3...)
    Serial.println("Firmware started: ESP32StartupErrorAnalyzer - BasicUsage");

    // Analyzer mit definierten Bedingungen starten
    ESP32StartupErrorAnalyzer analyzer(getStartupConditions());

    Serial.println("Start Analyzer...");
    analyzer.analyze(); // Bedingungen analysieren und entsprechende Callbacks ausführen
    Serial.println("Ready!");
}

/**
 * @brief Hauptprogrammschleife, die kontinuierlich ausgeführt wird.
 * 
 * In diesem Beispiel bleibt die Schleife leer, da die Analyse der Bedingungen
 * ausschließlich im `setup()`-Teil erfolgt.
 */
void loop() {
    // Hauptlogik
}
