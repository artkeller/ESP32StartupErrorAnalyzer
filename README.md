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
1. Download the library ZIP archive from GitHub: [https://github.com/artkeller/ESPRIC]
2. Unzip the archive into your Arduino libraries folder.

---

## Basic usage
```cpp
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

---

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
