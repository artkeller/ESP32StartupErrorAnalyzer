# ESPRIC: Source Documentation

## Overview
The `src` folder contains the implementation of the **ESPRIC** class, which is designed for analyzing ESP32 startup conditions, executing corresponding callbacks, and providing detailed insights into matched and unmatched conditions. This README provides a high-level overview of the header and implementation files (`ESPRIC.h` and `ESPRIC.cpp`).

### Important Notice

- The ESPRIC library is specifically designed for ESP32 devices. Currently, no other MCU platform offers equivalent post-mortem analysis capabilities supported by this library. Please ensure that you are using this library with ESP32-compatible devices only.
- If you are looking for a more generic solution for cyber resilience and analysis across multiple platforms, please refer to the [CRATE project on GitHub](http://).


---

## Files

### ESPRIC.h
This header file defines the `ESPRIC` class and its associated types, structures, and methods. The key components include:

- **ESPRIC Class**
  - A utility class for analyzing and handling ESP32 startup conditions.

- **Key Features**
  - Evaluate a set of predefined or dynamically added conditions.
  - Execute associated callbacks for matched conditions.
  - Optional default callback for unmatched conditions.
  - Provides detailed analysis results.

#### Key Elements

1. **Type Aliases**
   - `Condition`: A `std::function<bool()>` representing a condition to evaluate.
   - `Callback`: A `std::function<void()>` representing a callback to execute.

2. **Structures**
   - `ESPRIC_Condition`:
     - Represents a pair of a condition and its associated callback.
   - `AnalysisResult`:
     - Tracks the number of matched and unmatched conditions after analysis.

3. **Methods**
   - `ESPRIC` Constructor:
     - Initializes with predefined conditions and an optional default callback.
   - `analyze`:
     - Evaluates conditions, executes callbacks, and returns an `AnalysisResult`.
   - `addCondition`:
     - Allows dynamic addition of new conditions and callbacks.

### ESPRIC.cpp
This source file contains the implementation of the `ESPRIC` class methods defined in the header file.

#### Method Implementations

1. **Constructor**
   - Initializes the analyzer with predefined conditions and an optional default callback.

2. **analyze**
   - Iterates through conditions, executes callbacks for matched conditions, and provides an analysis result containing counts of matched and unmatched conditions.

3. **addCondition**
   - Dynamically adds a condition and its associated callback during runtime.

---

## Example Usage
```cpp
#include "ESPRIC.h"

void exampleCallback() {
    Serial.println("Condition met!");
}

void defaultCallback() {
    Serial.println("No conditions matched.");
}

void setup() {
    // Initialize Serial for debugging
    Serial.begin(115200);

    // Define conditions
    ESPRIC::Condition condition1 = []() -> bool {
        return digitalRead(5) == HIGH; // Example: Check GPIO pin 5 state
    };

    ESPRIC::Condition condition2 = []() -> bool {
        return millis() > 10000; // Example: Check uptime
    };

    // Create ESPRIC instance
    ESPRIC espric({{condition1, exampleCallback}, {condition2, exampleCallback}}, defaultCallback);

    // Analyze conditions
    ESPRIC::AnalysisResult result = espric.analyze();

    // Log results
    Serial.printf("Matched: %d, Unmatched: %d\n", result.matched, result.unmatched);
}

void loop() {
    // Nothing to do here
}
```

---

## Notes
- Ensure proper initialization of ESP32 peripherals (e.g., GPIO, timers) before analyzing conditions.
- The library is designed to be extendable for advanced use cases, such as environment monitoring or deep-sleep health checks.

---

## License
This library is open-source and released under the [CC0 1.0 Universal](../LICENSE).

---

## Contributions
Feel free to contribute by submitting issues or pull requests on the project repository.
