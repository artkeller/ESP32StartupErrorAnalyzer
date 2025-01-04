# Timing

## Übersicht
Der Ordner **timing** dient dazu, Laufzeitmessungen und Tests zu dokumentieren, um Performanceaussagen zu treffen. Hier werden spezifische Szenarien auf einem ESP32 evaluiert, insbesondere im Hinblick auf das Verhalten in Deep-Sleep-Modi. Die Ergebnisse sollen helfen, die Stabilität und Funktionalität von Power-Down-Domain-Konfigurationen zu validieren.

### Hardware
- **Mikrocontroller**: ESP32 (Modell: Atom, 240 MHz Taktung)

### Inhalt
- **Code**:
  - `ValidatePowerDownDomainConditions.ino`: Hauptsketch zur Validierung.
  - `PowerDownDomainConditions.h`: Header-Datei zur Definition und Konfiguration der Power-Down-Domains.
- **Ergebnisse**:
  - Detaillierte Protokolle über Teststatus (Erfolg/Fehler).

---

## ValidatePowerDownDomainConditions.ino

### Ziel
Dieser Sketch prüft die Konfiguration von Power-Down-Domains des ESP32 während des Deep-Sleep-Modus. Dabei werden vordefinierte Bedingungen ("Conditions") evaluiert und detaillierte Protokolle erstellt.

### Funktionsweise
1. **Setup-Phase**:
   - Initialisiert die serielle Kommunikation.
   - Ruft die Bedingungen aus `PowerDownDomainConditions.h` ab.
2. **Tests**:
   - Iteriert über jede Bedingung, testet sie und protokolliert die Ergebnisse.
   - Im Fehlerfall wird eine definierte Callback-Funktion aufgerufen.
3. **Protokollierung**:
   - Ergebnisse werden als Log-Ausgaben dokumentiert:
     - Erfolg: "Condition passed."
     - Fehler: "Condition failed."

### Code
Ein Auszug des Sketches:
```cpp
#include <vector>
#include "PowerDownDomainConditions.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  auto conditions = definePowerDownDomainConditions();
  testPowerDownDomainConditions(conditions);
}

void loop() {}
```

---

## PowerDownDomainConditions.h

### Ziel
Definiert die Power-Down-Domain-Bedingungen und zugehörige Fehler-Callbacks. Diese Datei ist modular aufgebaut, um flexibel neue Domains hinzuzufügen.

### Struktur
1. **PowerDownDomainCondition**:
   - Struktur zur Beschreibung einer Bedingung:
     - Name der Domain.
     - Funktion zur Prüfung der Bedingung.
     - Callback-Funktion bei Fehlern.
2. **definePowerDownDomainConditions()**:
   - Liefert eine Liste aller zu prüfenden Domains:
     - RTC8M, RTC_FAST_MEM, RTC_SLOW_MEM, RTC_PERIPH, XTAL, VDDSDIO.
     - CPU (nur, wenn vom SoC unterstützt).

### Code-Beispiel
Ein Eintrag der Bedingungsliste:
```cpp
{
  "RTC8M PD Domain",
  []() { return isError(esp_sleep_pd_config(ESP_PD_DOMAIN_RTC8M, ESP_PD_OPTION_OFF), "RTC8M"); },
  []() { log_e("Failed to configure 'RTC8M' powerdown domain."); }
},
```

---

## Ergebnisse

### Log-Ausgabe
Mit Debug-Level "Info" wurde folgender Bericht generiert:
```log
[  1044][I][ValidatePowerDownDomainConditions.ino:43] testPowerDownDomainConditions(): Starting 'PowerDownDomainConditions' Test Report:

[  1046][I][ValidatePowerDownDomainConditions.ino:66] testPowerDownDomainConditions(): All conditions passed.
```

### Interpretation

- **Alle Bedingungen bestanden**:
  - Alle Power-Down-Domains konnten erfolgreich konfiguriert werden.
  - Keine Fehler traten auf.

- **Ziel erreicht**:
  - Die Konfiguration ist stabil und funktional.
  
- **Laufzeit**:
  - Die gemessene Laufzeit betrug 2 ms (Startzeit: 1044 ms, Endzeit: 1046 ms) und liegt somit innerhalb akzeptabler Grenzen für die durchgeführten Konfigurationen.




