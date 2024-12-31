# Varianten (ALPHA Release!)

Die **`ESP32StartupErrorAnalyzer`**-Bibliothek erweitert die Flexibilität und Modularität für alle ESP32-Varianten und stellt sicher, dass sie optimal konfiguriert ist.  

## 1. **Variantenvielfalt**  

Die Bibliothek ist mit allen bekannten ESP32-Modellen (Stand 2024) kompatibel, einschließlich **ESP32**, **ESP32-C2**, **ESP32-C3**, **ESP32-C5**, **ESP32-S2**, **ESP32-S3**, **ESP32-H2** und **ESP32-P4**.  
Dabei bleiben viele Grundfunktionen einheitlich, während spezifische Erweiterungen und Anpassungen je nach Modell verfügbar sind.  

---

## 2. **Verzeichnisstruktur für Varianten**  

Die spezifischen Konfigurationen und Funktionen für verschiedene ESP32-Modelle sind im Verzeichnis `variants/` organisiert. Jede ESP32-Variante erhält eine eigene Template-Datei, die Reset- und Wakeup-Gründe sowie zugehörige Callbacks beschreibt.  

```
/ESPRIC
:
├── /src
│   ├── ESP32StartupErrorAnalyzer.cpp
│   ├── ESP32StartupErrorAnalyzer.h
:
└── /variants
    ├── ESP32-C2_template.h
    ├── ESP32-C3_template.h
    ├── ESP32-C5_template.h
    ├── ESP32-C6_template.h
    ├── ESP32-H2_template.h
    ├── ESP32-P4_template.h
    ├── ESP32-S2_template.h
    ├── ESP32-S3_template.h
    └── ESP32_template.h
```

---

## 3. **Reset-Gründe (`esp_reset_reason`)**  

Die Funktion `esp_reset_reason()` liefert den Grund für einen Reset. Die gängigsten Reset-Gründe sind modellübergreifend einheitlich:  

- **ESP_RST_PANIC**: Software-Panic-Reset.  
- **ESP_RST_POWERON**: Reset nach einem Power-On-Ereignis.  
- **ESP_RST_BROWNOUT**: Reset aufgrund einer Unterspannung.  
- **ESP_RST_SW**: Software-Reset.  
- **ESP_RST_DEEPSLEEP**: Reset nach einem Tiefschlafmodus.  
- **ESP_RST_EXT**: Reset durch ein externes Signal.  

Einige Varianten (z. B. **ESP32-S2**, **ESP32-S3**) bieten zusätzliche Reset-Gründe, wie **ESP_RST_USB**, **ESP_RST_PWR_GLITCH** oder **ESP_RST_CPU_LOCKUP**.  

---

## 4. **Wakeup-Gründe (`esp_sleep_get_wakeup_cause`)**  

Die Funktion `esp_sleep_get_wakeup_cause()` zeigt an, was den ESP32 aus dem Schlafmodus geweckt hat. Häufige Wakeup-Gründe sind:  

- **ESP_SLEEP_WAKEUP_TIMER**: Timer-basierter Wakeup.  
- **ESP_SLEEP_WAKEUP_GPIO**: GPIO-bedingter Wakeup.  
- **ESP_SLEEP_WAKEUP_TOUCHPAD**: Wakeup durch Touchpad-Interrupt.  
- **ESP_SLEEP_WAKEUP_EXT0/EXT1**: Externer Wakeup.  

Auch hier haben neuere Varianten (wie der **ESP32-C3** und **ESP32-H2**) möglicherweise zusätzliche Wakeup-Gründe, die durch neue Funktionen wie erweiterte Energiemodi oder Peripherie unterstützt werden.  

---

## 5. **Modellbezogene Erweiterungen (z. B. ESP32-C2, ESP32-H2, ESP32-P4)**  

Modelle wie der **ESP32-H2** und **ESP32-P4** integrieren neue Funktionen und Peripherien. Dazu gehören erweiterte Reset- und Wakeup-Gründe oder zusätzliche Analyseoptionen.  

---

## 6. **Kompatibilität der Bibliothek**  

Die Bibliothek wurde für eine breite Modellabdeckung entwickelt und ist kompatibel mit allen derzeit verfügbaren ESP32-Varianten. Anpassungen und Erweiterungen für spezifische Varianten werden durch die `variants/`-Struktur organisiert.  

### Zukünftige Entwicklungsziele:  
- Automatische Aktivierung nur relevanter Fehlerbedingungen per `#ifdef`.  
- Validierung und Tests auf allen ESP32-Modellen, einschließlich zukünftiger Varianten.  

---

## 7. **More**  

Die Reset- und Wakeup-Gründe basieren auf zentral definierten Enumerationen im **ESP-IDF**-Framework:  

### Reset-Gründe (`esp_reset_reason_t`)  

```cpp
/**
 * @brief Enumeration der möglichen Reset-Ursachen für ESP32-Varianten.
 * 
 * Diese Enumeration definiert die verschiedenen Gründe, warum ein ESP32-Mikrocontroller
 * einen Reset ausführen kann. Die Gründe können hardwarebedingt (z. B. Stromausfall),
 * softwarebedingt (z. B. ein Watchdog-Timer) oder durch externe Ereignisse ausgelöst sein.
 *
 * Die Reset-Ursachen können je nach ESP32-Variante leicht variieren. Diese Liste basiert auf
 * den Definitionen aus dem ESP-IDF Framework (Version 5.3.2).
 *
 * @note Einige Reset-Ursachen sind nicht auf allen Varianten verfügbar. Details finden Sie in
 *       den ESP-IDF Dokumentationen zu den jeweiligen Varianten.
 *
 * @enum esp_reset_reason_t
 */
typedef enum {
    ESP_RST_UNKNOWN,    //!< Reset-Ursache konnte nicht bestimmt werden.
    ESP_RST_POWERON,    //!< Reset durch ein Power-On-Ereignis.
    ESP_RST_EXT,        //!< Reset durch externes Signal (nicht anwendbar auf ESP32).
    ESP_RST_SW,         //!< Software-Reset durch `esp_restart`.
    ESP_RST_PANIC,      //!< Software-Reset aufgrund eines Ausnahmepanics.
    ESP_RST_INT_WDT,    //!< Reset durch Interrupt-Watchdog (Software oder Hardware).
    ESP_RST_TASK_WDT,   //!< Reset durch Task-Watchdog.
    ESP_RST_WDT,        //!< Reset durch andere Watchdogs.
    ESP_RST_DEEPSLEEP,  //!< Reset nach Verlassen des Deep-Sleep-Modus.
    ESP_RST_BROWNOUT,   //!< Brownout-Reset (Software oder Hardware).
    ESP_RST_SDIO,       //!< Reset über SDIO-Schnittstelle.
    ESP_RST_USB,        //!< Reset durch USB-Peripherie.
    ESP_RST_JTAG,       //!< Reset durch JTAG.
    ESP_RST_EFUSE,      //!< Reset aufgrund eines eFuse-Fehlers.
    ESP_RST_PWR_GLITCH, //!< Reset aufgrund eines erkannten Stromstoßes.
    ESP_RST_CPU_LOCKUP  //!< Reset durch CPU-Blockierung (doppelter Ausnahmefehler).
} esp_reset_reason_t;
```

### Wakeup-Gründe (`esp_sleep_source_t`)  

```cpp
/**
 * @brief Enumeration der Wakeup-Gründe aus dem Schlafmodus.
 *
 * Diese Enumeration beschreibt die möglichen Gründe, warum ein ESP32-Mikrocontroller
 * aus dem Schlafmodus aufwacht. Dazu gehören externe Signale, Timer-basierte
 * Wakeups oder interne Ereignisse wie GPIO-Interrupts.
 *
 * Die Wakeup-Gründe sind je nach ESP32-Variante unterschiedlich. Diese Liste basiert auf
 * den Definitionen aus dem ESP-IDF Framework (Version 5.3.2).
 *
 * @note Einige Wakeup-Quellen, wie z. B. WiFi oder Bluetooth, sind nur in bestimmten Varianten verfügbar.
 *
 * @enum esp_sleep_source_t
 */
typedef enum {
    ESP_SLEEP_WAKEUP_UNDEFINED,    //!< Kein definierter Wakeup-Grund.
    ESP_SLEEP_WAKEUP_ALL,          //!< Deaktiviert alle Wakeup-Quellen (nicht direkt ein Wakeup-Grund).
    ESP_SLEEP_WAKEUP_EXT0,         //!< Wakeup durch externes Signal über RTC_IO.
    ESP_SLEEP_WAKEUP_EXT1,         //!< Wakeup durch externes Signal über RTC_CNTL.
    ESP_SLEEP_WAKEUP_TIMER,        //!< Wakeup durch Timer.
    ESP_SLEEP_WAKEUP_TOUCHPAD,     //!< Wakeup durch Touchpad-Interrupt.
    ESP_SLEEP_WAKEUP_ULP,          //!< Wakeup durch ULP-Programm.
    ESP_SLEEP_WAKEUP_GPIO,         //!< Wakeup durch GPIO (nur Light Sleep auf ESP32, S2 und S3).
    ESP_SLEEP_WAKEUP_UART,         //!< Wakeup durch UART (nur Light Sleep).
    ESP_SLEEP_WAKEUP_WIFI,         //!< Wakeup durch WiFi (nur Light Sleep).
    ESP_SLEEP_WAKEUP_COCPU,        //!< Wakeup durch Co-Prozessor-Interrupt.
    ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG, //!< Wakeup durch Co-Prozessor-Absturz.
    ESP_SLEEP_WAKEUP_BT            //!< Wakeup durch Bluetooth (nur Light Sleep).
} esp_sleep_source_t;
```

### Links:  
- [esp_system.h in ESP-IDF](https://github.com/espressif/esp-idf/blob/v5.3.2/components/esp_system/include/esp_system.h)  
- [esp_sleep.h in ESP-IDF](https://github.com/espressif/esp-idf/blob/v5.3.2/components/esp_hw_support/include/esp_sleep.h)  

--- 


