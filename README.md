# ESP32StartupErrorAnalyzer

ESP32StartupErrorAnalyzer is an Arduino library that facilitates the analysis and handling of startup error conditions on ESP32 devices. 

## Features
- Define conditions that are checked during startup.
- Call specific callbacks for detected errors.
- Supports an optional default callback.

## Installation
1. Download the ZIP file.
2. Open the Arduino IDE.
3. Go to `Sketch` -> `Include Library` -> `Add ZIP Library`.
4. Select the downloaded ZIP file.

## Example
A simple example can be found in the folder `examples/BasicUsage`.

This example shows how to use the ESP32StartupErrorAnalyzer library to analyse the causes of errors and reset conditions when the ESP32 starts up. At startup, the library automatically checks the state of the ESP32 and executes corresponding callback functions when an error cause (such as a power-on reset or a wakeup by timer) is detected. The results are output via the serial console.

This example ensures that the ESP32 is monitored during boot and that error conditions or special events, such as a reset or wakeup, are detected immediately.

```cpp
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
```

## Requirements
- This library is for ESP32 devices only.
- Arduino IDE or PlatformIO with ESP32 support.
