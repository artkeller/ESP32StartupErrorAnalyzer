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

The example shows how the ESP32StartupErrorAnalyzer library is used to analyse specific startup conditions on an ESP32 and execute corresponding actions.

Defining the conditions and callbacks:

A function getStartupConditions() creates a list of conditions (ErrorCondition) to be checked. Each condition consists of:

- Condition: A lambda function that returns true if the condition is fulfilled.
- Callback: A lambda function that is executed if the condition is fulfilled.

In this example:

- Condition 1 checks whether the reset was caused by a panic error (ESP_RST_PANIC). The callback issues a corresponding message.
- Condition 2 checks whether the device was woken from sleep mode by an external signal (ESP_SLEEP_WAKEUP_EXT0). A message is also output here.

Initialisation in setup():

- The ESP32StartupErrorAnalyzer is initialised with the defined conditions from getStartupConditions().
' The analysis of the conditions is started with analyze(). Each fulfilled error or wake-up reason leads to the associated callback being called.

Main logic in the loop():

- The loop() function contains the main logic of the application. It remains empty in this example, as the focus is on the startup error analysis.

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

    // Instanziierung des Fehleranalysators
    ESP32StartupErrorAnalyzer analyzer(getStartupConditions());
    
    // Fehleranalyse starten
    analyzer.analyze();
}

void loop() {
    // Hauptlogik
}
```

## Requirements
- This library is for ESP32 devices only.
- Arduino IDE or PlatformIO with ESP32 support.
