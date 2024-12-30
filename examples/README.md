# ESPRIC Examples

This folder contains a series of examples demonstrating how to use the ESPRIC library for analyzing and responding to ESP32 reset conditions. Each example focuses on a specific use case or feature.

## Examples

>>>>HIER BITTE LISTE DER EXAPLES MIT HYPERSPRUNG AUF DIE PASSENDEN LABELS<<<<

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

### 02-AdvancedConditions
**Description coming soon.**

### 03-DeepSleepChecks
**Description coming soon.**

### 04-GPIOConditions
**Description coming soon.**

### 05-RTCVariableCheck
**Description coming soon.**

### 06-EnvironmentConditions
**Description coming soon.**

### 07-SafetyAndSecurity
**Description coming soon.**

---

