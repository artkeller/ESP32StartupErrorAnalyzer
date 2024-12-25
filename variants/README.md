# Varianten (ALPHA Release!)

Erweiterung, um die Flexibilität und Erweiterbarkeit der Bibliothek zu erhöhen und sicherzustellen, dass sie für alle ESP32-Varianten optimal konfiguriert ist. 

### 1. **Variantenvielfalt**

Die `ESP32StartupErrorAnalyzer`-Bibliothek, ist grundsätzlich mit allen im Jahr 2024 bwkannten ESP32-Modellen, wie **ESP32**, **ESP32-C2**, **ESP32-C3**, **ESP32-C5**, **ESP32-S2**, **ESP32-S3**, **ESP32-H2** und **ESP32-P4** kompatibel. Es gibt Übereinstimmungen und UNterschiede, wenn die Bibliothek auf allen diesen Varianten verwendet werden:

### 2. **Verzeichnisstruktur für Varianten**

Das Verzeichnis `variants/` enthält für jede ESP32-Variante eine eigene Template-Datei, die die spezifischen Reset- und Wakeup-Gründe sowie die zugehörigen Callback-Funktionen enthält.

```
/ESP32StartupErrorAnalyzer
│
├── /src
│   └── ESP32StartupErrorAnalyzer.cpp
│   └── ESP32StartupErrorAnalyzer.h
:
├── /variants
│   ├── ESP32-C2_template.h
│   ├── ESP32-C3_template.h
│   ├── ESP32-C5_template.h
│   ├── ESP32-C6_template.h
│   ├── ESP32-H2_template.h
│   ├── ESP32-P4_template.h
│   ├── ESP32-S2_template.h
│   ├── ESP32-S3_template.h
│   └── ESP32_template.h
_
└── /examples
    ├── ...
    ├── CustomConditionsExample
    └── ErrorCounterWithDefault
```

### 3. **Reset-Gründe (`esp_reset_reason`)**

Die Funktion `esp_reset_reason()` gibt den Grund für den Reset zurück. In der Regel sind diese Gründe (wie **ESP_RST_PANIC**, **ESP_RST_POWERON**, etc.) in den verschiedenen ESP32-Varianten **kompatibel**, aber es gibt auch einige Unterschiede zwischen den Varianten. Die gängigsten Reset-Gründe sind:

- **ESP_RST_PANIC**: Auftritt, wenn der ESP32 wegen eines Software-Panics neu startet.
- **ESP_RST_POWERON**: Tritt nach dem Einschalten des ESP32 auf.
- **ESP_RST_BROWNOUT**: Wird durch eine Unterspannungsbedingung ausgelöst.
- **ESP_RST_SW**: Software-Reset.
- **ESP_RST_DEEPSLEEP**: Tiefschlaf-Reset.
- **ESP_RST_EXT**: Reset durch externes Signal.

Die oben genannten Gründe sind in den meisten Varianten der ESP32-Serie **gemeinsam**, aber einige neue Modelle wie **ESP32-S2** oder **ESP32-S3** haben zusätzliche spezifische Reset-Gründe. Die neueren Modelle wie der **ESP32-C3** und **ESP32-H2** haben möglicherweise auch erweiterte oder leicht unterschiedliche Reset-Gründe aufgrund von neuen Peripherien oder Funktionen, die in diesen Chips integriert sind.

### 4. **Wakeup-Gründe (`esp_sleep_get_wakeup_cause`)**

Die `esp_sleep_get_wakeup_cause()`-Funktion gibt an, wie der ESP32 aus dem Schlafmodus geweckt wurde. Auch hier gibt es Unterschiede zwischen den Varianten. Gängige Wakeup-Gründe sind:

- **ESP_SLEEP_WAKEUP_UNDEFINED**: Kein spezifizierter Wakeup-Grund.
- **ESP_SLEEP_WAKEUP_EXT0**: Externer Wakeup.
- **ESP_SLEEP_WAKEUP_EXT1**: Wakeup von externem Gerät über einen anderen Pin.
- **ESP_SLEEP_WAKEUP_TIMER**: Timer-basierter Wakeup.
- **ESP_SLEEP_WAKEUP_TOUCHPAD**: Wakeup durch einen Touchpad-Interrupt.
- **ESP_SLEEP_WAKEUP_GPIO**: Wakeup durch GPIO-Pin.
  
Die Wakeup-Gründe sind grundsätzlich in allen Varianten ähnlich, jedoch können **neuere Modelle** (wie der **ESP32-S2** oder **ESP32-C3**) zusätzliche Wakeup-Gründe oder -Methoden haben, die auf neuen Funktionalitäten oder unterschiedlichen Energiemodi basieren.

### 5. **Hinweis für neue Varianten (z. B. ESP32-C2, ESP32-H2, ESP32-P4)**

Die **ESP32-C2**, **ESP32-H2**, **ESP32-P4** und andere zukünftige Varianten können **unterschiedliche Reset- und Wakeup-Gründe** sowie erweiterte Funktionen bieten. Hier ist zu erwarten, dass einige Modelle entweder neue spezialisierte Reset-/Wakeup-Gründe haben oder durch neue Features zusätzliche Optionen zur Fehleranalyse bieten.

### 6. **Kompatibilität der Bibliothek**

Insgesamt sind die meisten grundlegenden Reset-Gründe und Wakeup-Gründe in allen ESP32-Varianten identisch bzww. ähnlich und die  `ESP32StartupErrorAnalyzer`-Bibliothek sollte grundsätzlich mit allen Varianten kompatibel sein. Um  sicherzustellen, dass diese Bibliothek auch mit den neuesten Varianten (wie C2, C3, H2, P4) perfekt funktioniert, sind noch zusätzliche Tests und ggfs. Anpassungen vorzunehmen, vor allem, wenn es spezifische Fehlerbedingungen oder spezielle Reset-/Wakeup-Gründe in diesen neuen Modellen gibt.

#### Weiteres Vorgehen/TODOS
- **Testen auf allen Varianten**
- **Modularität**: Erweiterung der Bibliothek, damit sie bei der Initialisierung die Verfügbarkeit bestimmter Reset-/Wakeup-Gründe überprüft und nur die relevanten Fehlerbedingungen aktiviert. Dies soll durch `#ifdef`-Bedingungen für verschiedene Chip-Modelle erfolgen.
- **Zukünftige Varianten berücksichtigen**: Sicherstellung, dass bei neuen Modellen wie dem ESP32-H2 oder ESP32-P4 neue Reset-/Wakeup-Gründe berücksichtigt werden.
