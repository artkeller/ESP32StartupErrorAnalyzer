### Timing

## Overview
The **timing** folder is dedicated to documenting runtime measurements and tests to provide performance insights. It focuses on specific scenarios on an ESP32, particularly regarding behavior in deep-sleep modes. The results aim to validate the stability and functionality of power-down domain configurations.

### Hardware
- **Microcontroller**: ESP32 (Model: Atom, 240 MHz clock)

### Compiler Settings
- **Core Debug Level**: 'Info'

### Content
- **Code**:
  - `ValidatePowerDownDomainConditions.ino`: Main sketch for validation.
  - `PowerDownDomainConditions.h`: Header file defining and configuring power-down domains.
- **Results**:
  - Detailed logs of test statuses (success/failure).

---

## ValidatePowerDownDomainConditions.ino

### Objective
This sketch verifies the configuration of ESP32 power-down domains during deep-sleep mode. Predefined conditions are evaluated, and detailed logs are generated. In this initial test, generic code was used instead of the ESPRIC library.

### Functionality
1. **Setup Phase**:
   - Initializes serial communication.
   - Retrieves conditions from `PowerDownDomainConditions.h`.
2. **Tests**:
   - Iterates through each condition, tests it, and logs the results.
   - Calls a defined callback function in case of failure.
3. **Logging**:
   - Logs results as:
     - Success: "Condition passed."
     - Failure: "Condition failed."

### Code
A snippet of the sketch:
```cpp
#include <vector>
#include "PowerDownDomainConditions.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  auto conditions = definePowerDownDomainConditions();
  testPowerDownDomainConditions(conditions);
}

void loop() {}
```

---

## PowerDownDomainConditions.h

### Objective
Defines power-down domain conditions and associated error callbacks. This file is modularly designed to flexibly add new domains.

### Structure
1. **PowerDownDomainCondition**:
   - A structure describing a condition:
     - Domain name.
     - Function to check the condition.
     - Callback function for errors.
2. **definePowerDownDomainConditions()**:
   - Returns a list of all domains to be tested:
     - RTC8M, RTC_FAST_MEM, RTC_SLOW_MEM, RTC_PERIPH, XTAL, VDDSDIO.
     - CPU (if supported by the SoC).

### Code Example
An entry from the condition list:
```cpp
{
  "RTC8M PD Domain",
  []() { return isError(esp_sleep_pd_config(ESP_PD_DOMAIN_RTC8M, ESP_PD_OPTION_OFF), "RTC8M"); },
  []() { log_e("Failed to configure 'RTC8M' powerdown domain."); }
},
```

### Test Procedure
Six domain conditions were tested: 

Configured domains:
- RTC8M
- RTC_FAST_MEM
- RTC_SLOW_MEM
- RTC_PERIPH
- XTAL
- VDDSDIO

The responses were evaluated for correctness.

---

## Results

### Log Output
With the debug level set to "Info," the following report was generated:
```log
[  1044][I][ValidatePowerDownDomainConditions.ino:43] testPowerDownDomainConditions(): Starting 'PowerDownDomainConditions' Test Report:

[  1046][I][ValidatePowerDownDomainConditions.ino:66] testPowerDownDomainConditions(): All conditions passed.
```

### Interpretation

- **All Conditions Passed**:
  - All power-down domains were successfully configured.
  - No errors occurred.

- **Objective Achieved**:
  - The configuration is stable and functional.
  
- **Runtime**:
  - The measured runtime was 2 ms (start time: 1044 ms, end time: 1046 ms), which is within acceptable limits for the performed configurations.

