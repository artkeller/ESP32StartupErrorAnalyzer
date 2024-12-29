ATTN: ALPHA VERSION - IN PROGRESS

# ESPRIC: ESP32 Reboot Investigation and Context Integrity Check

## Introduction
ESPRIC is a robust and flexible open-source library for the ESP32 specifically designed to enhance the reliability and security of embedded applications. By conducting an in-depth analysis of the system state post-reboot, ESPRIC enables precise error diagnosis and swift recovery of functionality.

## Installation
**Using the Arduino Library Manager:**
1. Open the Arduino IDE.
2. Go to "Sketch" -> "Include Library" -> "Manage Libraries".
3. Search for "ESPRIC" and install the library.

**Manual installation:**
1. Download the library ZIP archive from GitHub: [Link to GitHub repository]
2. Unzip the archive into your Arduino libraries folder.

## Basic usage
```cpp
#include <ESPRIC.h>
#include <ESPRIC.h>

// Function to define the conditions and their corresponding callbacks
std::vector<ESPRIC::ESPRIC_Condition> defineConditions() {
  return {
    // Condition for an unknown reset reason
    {[]() { return esp_reset_reason() == ESP_RST_UNKNOWN; },
     []() { Serial.println("Memory reflashed? (Unknown reset reason)"); }},
     
    // Condition for a power-on reset
    {[]() { return esp_reset_reason() == ESP_RST_POWERON; },
     []() { Serial.println("Power-on detected."); }},
     
    // Condition for a panic reset
    {[]() { return esp_reset_reason() == ESP_RST_PANIC; }, 
     []() { 
       Serial.println("Panic reset detected. STOP!"); 
       while (1) {}; 
     }},
  };
}

// Function to initialize ESPRIC and perform analysis
void initializeESPRIC() {
  Serial.begin(115200);

  // Create ESPRIC instance with the defined conditions
  ESPRIC espric(defineConditions());

  // Analyze the conditions and execute callbacks
  auto result = espric.analyze();

  // Optional: Log results
  Serial.printf("Conditions matched: %d, unmatched: %d\n", 
                result.matched, result.unmatched);
}

void setup() {
  initializeESPRIC();
}

void loop() {
  // Main application logic
}
```

## Advanced features
* **Customizable analysis depth:** Tailor the depth of the status analysis to your specific needs.
* **Support for various restart causes:** ESPRIC recognizes various reboot reasons such as watchdog, external reset, brownout, etc.
* **Flexible configuration:** Customize the library to your application using configuration options.
* **Extensibility:** Add your own modules to extend functionality.

## Use cases
* **Deep-sleep applications:** Ensure reliable recovery after waking from deep sleep.
* **Safety-critical applications:** Detect security risks and sabotage attempts.
* **IoT devices:** Improve the reliability and longevity of IoT devices.
* **Industrial automation:** Guarantee the operational readiness of machines and systems.

## Why ESPRIC?
* **Reliability:** ESPRIC provides a solid foundation for developing reliable embedded applications.
* **Flexibility:** The library is adaptable to a wide range of application scenarios.
* **Openness:** ESPRIC is open-source and released under a [license].
* **Community:** Join our community and benefit from the exchange with other developers.

## Contributing
We welcome any contributions! Whether it's bug reports, suggestions for improvements, or new features, every contribution is valued.

## License
ESPRIC is released under the Creative Commons Zero v1.0 Universal.

[https://github.com/artkeller/ESPRIC]
[Link to documentation]
[Link to forum or issue tracker]

## Tutorials

Detailed instructions for advanced use cases. TBD

## FAQ

Frequently asked questions and answers. TBD

## Changelog 

Overview of main changes in the different versions.

- version 0.2.0 Renaming lib
- version 0.1.0 Initial

## Future plans

Outlook on planned developments. TBD


---

DESCRIPTION DEPRICATED

# ESPRIC - ESP32 Reboot Investigation and Context Integrity Check

ESPRIC is an Arduino library that facilitates the analysis and handling of startup error conditions on ESP32 devices. 

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

This example shows how to use the **ESPRIC** library to analyse the causes of errors and reset conditions when the ESP32 starts up. At startup, the library automatically checks the state of the ESP32 and executes corresponding callback functions when an error cause (such as a power-on reset or a wakeup by timer) is detected. The results are output via the serial console.

The example `BasicUsage` shows how the **ESPRIC** library is used to analyse specific startup conditions on an ESP32 and execute corresponding actions.

### Defining the **conditions** and **callbacks**:

A function `getStartupConditions()` creates a list of conditions (ErrorCondition) to be checked. 
Each condition consists of:

- **Condition**: A lambda function that returns `true` if the condition is fulfilled.
- **Callback**: A lambda function that is executed if the condition is fulfilled.

### In this example:

- **Condition 1** checks whether the reset was caused by a panic error (`ESP_RST_PANIC`). The **callback** issues a corresponding message.
- **Condition 2** checks whether the device was woken from sleep mode by an external signal (`ESP_SLEEP_WAKEUP_EXT0`). A message is also output here.

### Initialisation in setup():

- The `ESPRIC` is initialised with the defined conditions from `getStartupConditions()`.
- The analysis of the conditions is started with `analyze()`. Each fulfilled error or wake-up reason leads to the associated callback being called.

### Main logic in the loop():

- The `loop()` function contains the main logic of the application. It remains empty in this example, as the focus is on the startup error analysis.

`BasicUsage.ino`:
```cpp

#include <ESPRIC.h>

// Define the conditions and callbacks.
std::vector<ESPRIC::ErrorCondition> getStartupConditions() {
    return {
        {[]() { return esp_reset_reason() == ESP_RST_PANIC; }, []() { Serial.println("Panik-Reset erkannt."); }},
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0; }, []() { Serial.println("Wakeup durch externes Signal."); }}
    };
}

void setup() {
    Serial.begin(115200);

    // Instanziierung des Fehleranalysators
    ESPRIC analyzer(getStartupConditions());
    
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
