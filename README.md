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
With this example, you can analyse the reset reason of an ESP32 and react flexibly to it. The ESPRIC library offers a modular structure that can be easily customised to meet specific requirements in your projects.

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

#### Step-by-step explanation:

1. **Definition of the conditions:**

   The `defineConditions()` function creates a list of conditions based on the reset reasons of the ESP32. Each condition consists of
  - **A condition function:** This checks whether there is a specific reset reason.
  - **A callback function:** This is executed if the condition applies.

  Example:
  - If the reset reason is `ESP_RST_UNKNOWN`, the following is output: ‘Memory reflashed? (Unknown reset reason)’.
  - In the case of an `ESP_RST_POWERON` (power-on reset), the following is output: ‘Power-on detected.’
  - In the event of an `ESP_RST_PANIC` (panic reset), a STOP loop is executed to analyse the status.

2. **Initialisation of the ESPRIC instance**:

   The library is initialised in the `initializeESPRIC()` function:
- The defined conditions are transferred.
- The analysis is carried out with `espric.analyze()`, whereby the conditions are checked and corresponding actions are triggered.
- In addition, the result is logged, indicating how many conditions were or were not fulfilled.

3. **Use in setup():**

   The `initialiseESPRIC()` function is called in the `setup()` block so that the analysis is performed when the device is started.

5. **Flexibility in loop():**

   The `loop()` block remains free for the main application, so that the developer can integrate the library into any application without restrictions for the main logic.


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
ESPRIC is released under the  [CC0 1.0 Universal](LICENSE).

[Link to documentation]

[Link to forum or issue tracker]

## Tutorials

Detailed instructions for advanced use cases. TBD

## FAQ

Frequently asked questions and answers. TBD

## Changelog 

Overview of main changes in the different versions.

- version 0.2.1 - Adoption of new examples
- version 0.2.0 - Renaming lib as ESPRIC
- version 0.1.0 - Initial pre-version/study

## Future plans

Outlook on planned developments:

- Automatic use of defaults based on variants with all RST and wakeup reasons as standard log() message

---
