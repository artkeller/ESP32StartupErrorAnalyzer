# ESPRIC Examples

This folder contains a series of examples demonstrating how to use the ESPRIC library for analyzing and responding to ESP32 reset conditions. Each example focuses on a specific use case or feature.

## Examples

- [01-BasicUsage](#01-basicusage)
- [02-ModularESPRICExample](#02-modularespricexample)
- [03-AdvancedConditions](#03-advancedconditions)
- [04-DeepSleepChecks](#04-deepsleepchecks)
- [05-GPIOConditions](#05-gpioconditions)
- [06-RTCVariableCheck](#06-rtcvariablecheck)
- [08-EnvironmentConditions](#76-environmentconditions)
- [08-SafetyAndSecurity](#08-safetyandsecurity)

### 01-BasicUsage

**Purpose**: Demonstrates the basic usage of the ESPRIC library to analyze reset causes and execute corresponding callback functions.

**Features**:
- Defines conditions for reset reasons such as unknown resets, power-on resets, and panic resets.
- Associates callback functions to each condition to log information or take specific actions.
- Outputs results to the serial interface.

**Code Overview**:
- `getMyESPRIC_Conditions()`: Defines a vector of `ESPRIC_Condition` objects, each consisting of a condition function and a callback function.
- `setup()`: Initializes the serial interface, sets up the ESPRIC analyzer with the defined conditions, and runs the analysis.
- `loop()`: Left empty in this example since all logic is handled in `setup()`.

**Example Output**:
```
Firmware started: ESPRIC - BasicUsage
Start Analyzer...
Power-on detected.
Ready!
```

**How to Run**:
1. Upload the sketch to your ESP32 using the Arduino IDE or PlatformIO.
2. Open the serial monitor at 115200 baud to view the output.

---

### 02-ModularESPRICExample

**Purpose**: Demonstrates how to use ESPRIC in a modular way by encapsulating restart conditions and their callbacks in an external header file.

**Features**:
- Keeps the main sketch lightweight and focused on initialization.
- Defines restart conditions and their corresponding callbacks in `RestartConditions.h`.
- Utilizes a modular design approach for reusability and better organization.

**Code Overview**:
- `getRestartConditions()`: Provided in `RestartConditions.h`, defines the conditions and callbacks for analyzing restart causes.
- `setup()`: Initializes the serial interface, creates an instance of the ESPRIC analyzer with predefined conditions, and runs the analysis.
- `loop()`: Left empty as all logic is executed in `setup()`.

**Example Output**:
```
Firmware started: ESPRIC - Modular Example
Starting Analyzer...
[ESPRIC] Power-on reset detected.
Analyzer Complete!
```

**How to Run**:
1. Ensure `RestartConditions.h` is in the same directory as the sketch.
2. Upload the sketch to your ESP32 using the Arduino IDE or PlatformIO.
3. Open the serial monitor at 115200 baud to view the output.

---

### 03-AdvancedConditions
**Description coming soon.**

### 04-DeepSleepChecks
**Description coming soon.**

### 05-GPIOConditions
**Description coming soon.**

### 06-RTCVariableCheck
**Description coming soon.**

### 07-EnvironmentConditions
**Description coming soon.**

### 08-SafetyAndSecurity
**Description coming soon.**

---
