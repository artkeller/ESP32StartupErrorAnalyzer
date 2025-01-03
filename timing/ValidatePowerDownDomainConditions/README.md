# **Timing**

## **Overview**
The **timing** folder documents runtime measurements and performance tests related to power-down domain behavior on an ESP32. These measurements primarily focus on deep-sleep mode to ensure stability and proper configuration of the power-down domains.

---

## **Summary**
- All tests confirmed the proper configuration of ESP32 power-down domains.
- Minimal runtime overhead was observed.
- The code is robust and ready for further deployment or integration with advanced libraries like ESPRIC.

---

## **Hardware**
- **Microcontroller**: ESP32  
  - Model: M5Atom  
  - Clock Speed: 240 MHz  

---

## **Content**
- **Code Files**:
  1. `ValidatePowerDownDomainConditions.ino`: Main sketch for validating the power-down domain configurations.
  2. `PowerDownDomainConditions.h`: Header file containing the definitions and configuration logic for power-down domains.

- **Results**:
  - Log outputs for test executions, including runtime performance, success, and failure details.

---

## **Code Details**

### **ValidatePowerDownDomainConditions.ino**

#### Objective
The sketch validates the ESP32 power-down domain configurations during deep-sleep mode by testing predefined conditions. It generates detailed logs for debugging and performance evaluation.

#### **Functionality**
1. **Setup Phase**:
   - Initializes serial communication (`Serial.begin()`).
   - Loads power-down domain configurations from `PowerDownDomainConditions.h`.
2. **Testing**:
   - Iterates through the list of domain conditions.
   - Evaluates each condition and logs results.
   - Triggers a callback on failure to highlight the issue.
3. **Logging**:
   - Success message: "Condition passed."
   - Failure message: "Condition failed."

#### **Code Snippet**
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

### **PowerDownDomainConditions.h**

#### Objective
Defines the structure and logic for configuring and testing power-down domains. The file is modular, enabling the easy addition of new domain conditions.

#### **Structure**
1. **`PowerDownDomainCondition`**:
   - Contains:
     - **Domain Name**: A descriptive string.
     - **Condition Function**: Tests the domain configuration.
     - **Error Callback**: Executes in case of failure.
2. **`definePowerDownDomainConditions()`**:
   - Returns a list of predefined power-down domains for testing:
     - RTC8M, RTC_FAST_MEM, RTC_SLOW_MEM, RTC_PERIPH, XTAL, VDDSDIO.
     - Optionally includes CPU, depending on SoC support.

#### **Code Example**
A condition definition for the `RTC8M` domain:
```cpp
{
  "RTC8M PD Domain",
  []() { return isError(esp_sleep_pd_config(ESP_PD_DOMAIN_RTC8M, ESP_PD_OPTION_OFF), "RTC8M"); },
  []() { log_e("Failed to configure 'RTC8M' powerdown domain."); }
},
```

---

## **Test Results**

### **Test 1**

#### **Configuration**
- **Domains Tested**:
  - RTC8M, RTC_FAST_MEM, RTC_SLOW_MEM, RTC_PERIPH, XTAL, VDDSDIO.
- **Compiler Settings**:
  - Core Debug Level: **Info**.

#### **Log Output**
```log
[  1044][I][ValidatePowerDownDomainConditions.ino:43] testPowerDownDomainConditions(): Starting 'PowerDownDomainConditions' Test Report:
[  1046][I][ValidatePowerDownDomainConditions.ino:66] testPowerDownDomainConditions(): All conditions passed.
```

#### **Analysis**
- **Result**:
  - All power-down domains were successfully configured.
  - No errors were reported.
- **Runtime**:
  - 2 ms (Start: 1044 ms, End: 1046 ms).
- **Conclusion**:
  - The configuration is stable and functional.

---

### **Test 2**

#### **Configuration**
- **Domains Tested**:
  - Same as Test 1.
- **Compiler Settings**:
  - Core Debug Level: **Verbose**.

#### **Log Output**
```log
[    14][D][esp32-hal-cpu.c:244] setCpuFrequencyMhz(): PLL: 480 / 2 = 240 Mhz, APB: 80000000 Hz
[  1045][I][ValidatePowerDownDomainConditions.ino:43] testPowerDownDomainConditions(): Starting 'PowerDownDomainConditions' Test Report:

[  1047][D][ValidatePowerDownDomainConditions.ino:47] testPowerDownDomainConditions(): Testing Condition 1: RTC8M PD Domain
[  1057][D][ValidatePowerDownDomainConditions.ino:60] testPowerDownDomainConditions(): Condition 'RTC8M PD Domain' passed.

[  1068][D][ValidatePowerDownDomainConditions.ino:47] testPowerDownDomainConditions(): Testing Condition 2: RTC_FAST_MEM PD Domain
[  1080][D][ValidatePowerDownDomainConditions.ino:60] testPowerDownDomainConditions(): Condition 'RTC_FAST_MEM PD Domain' passed.

[  1091][D][ValidatePowerDownDomainConditions.ino:47] testPowerDownDomainConditions(): Testing Condition 3: RTC_SLOW_MEM PD Domain
[  1103][D][ValidatePowerDownDomainConditions.ino:60] testPowerDownDomainConditions(): Condition 'RTC_SLOW_MEM PD Domain' passed.

[  1114][D][ValidatePowerDownDomainConditions.ino:47] testPowerDownDomainConditions(): Testing Condition 4: RTC_PERIPH PD Domain
[  1126][D][ValidatePowerDownDomainConditions.ino:60] testPowerDownDomainConditions(): Condition 'RTC_PERIPH PD Domain' passed.

[  1137][D][ValidatePowerDownDomainConditions.ino:47] testPowerDownDomainConditions(): Testing Condition 5: XTAL PD Domain
[  1148][D][ValidatePowerDownDomainConditions.ino:60] testPowerDownDomainConditions(): Condition 'XTAL PD Domain' passed.

[  1159][D][ValidatePowerDownDomainConditions.ino:47] testPowerDownDomainConditions(): Testing Condition 6: VDDSDIO PD Domain
[  1170][D][ValidatePowerDownDomainConditions.ino:60] testPowerDownDomainConditions(): Condition 'VDDSDIO PD Domain' passed.

[  1181][I][ValidatePowerDownDomainConditions.ino:66] testPowerDownDomainConditions(): All conditions passed.
```

#### **Analysis**
- **Result**:
  - Each domain passed individual testing with detailed logs.
- **Runtime**:
  - 136 ms (from first domain initialization to completion).
- **Conclusion**:
  - Detailed debug logging confirmed functionality and stability.

---

### **Test 3**

#### **Configuration**
- **Domains Tested**:
  - RTC8M, RTC_FAST_MEM, RTC_SLOW_MEM, RTC_PERIPH, XTAL, VDDSDIO.
- **Compiler Settings**:
  - Core Debug Level: **Verbose**.
- **Modification**:
  - The `isError()` function emulates errors by setting `err = 0xFFFF`.

#### **Code Snippet**
Modified `isError()` function:
```cpp
bool isError(esp_err_t err, const char* domainName) {
  err = 0xFFFF; // Test Error condition
  if (err != ESP_OK) {
    log_e("Configuration failed for %s: Error code: 0x%X", domainName, err);
    return true;
  }
  return false;
}
```

#### **Log Output**
```log
[    14][D][esp32-hal-cpu.c:244] setCpuFrequencyMhz(): PLL: 480 / 2 = 240 Mhz, APB: 80000000 Hz
[  1045][I][ValidatePowerDownDomainConditions.ino:43] testPowerDownDomainConditions(): Starting 'PowerDownDomainConditions' Test Report:

[  1047][D][ValidatePowerDownDomainConditions.ino:47] testPowerDownDomainConditions(): Testing Condition 1: RTC8M PD Domain
[  1057][E][ValidatePowerDownDomainConditions.ino:26] isError(): Configuration failed for RTC8M: Error code: 0xFFFF
[  1068][E][ValidatePowerDownDomainConditions.ino:54] testPowerDownDomainConditions(): Condition 'RTC8M PD Domain' failed.
[  1078][E][PowerDownDomainConditions.h:60] operator()(): Failed to configure 'RTC8M' powerdown domain.

[  1087][D][ValidatePowerDownDomainConditions.ino:47] testPowerDownDomainConditions(): Testing Condition 2: RTC_FAST_MEM PD Domain
[  1099][E][ValidatePowerDownDomainConditions.ino:26] isError(): Configuration failed for RTC_FAST_MEM: Error code: 0xFFFF
[  1110][E][ValidatePowerDownDomainConditions.ino:54] testPowerDownDomainConditions(): Condition 'RTC_FAST_MEM PD Domain' failed.
[  1121][E][PowerDownDomainConditions.h:65] operator()(): Failed to configure 'RTC_FAST_MEM' powerdown domain.

[  1131][D][ValidatePowerDownDomainConditions.ino:47] testPowerDownDomainConditions(): Testing Condition 3: RTC_SLOW_MEM PD Domain
[  1142][E][ValidatePowerDownDomainConditions.ino:26] isError(): Configuration failed for RTC_SLOW_MEM: Error code: 0xFFFF
[  1153][E][ValidatePowerDownDomainConditions.ino:54] testPowerDownDomainConditions(): Condition 'RTC_SLOW_MEM PD Domain' failed.
[  1164][E][PowerDownDomainConditions.h:70] operator()(): Failed to configure 'RTC_SLOW_MEM' powerdown domain.

[  1174][D][ValidatePowerDownDomainConditions.ino:47] testPowerDownDomainConditions(): Testing Condition 4: RTC_PERIPH PD Domain
[  1185][E][ValidatePowerDownDomainConditions.ino:26] isError(): Configuration failed for RTC_PERIPH: Error code: 0xFFFF
[  1196][E][ValidatePowerDownDomainConditions.ino:54] testPowerDownDomainConditions(): Condition 'RTC_PERIPH PD Domain' failed.
[  1207][E][PowerDownDomainConditions.h:75] operator()(): Failed to configure 'RTC_PERIPH' powerdown domain.

[  1217][D][ValidatePowerDownDomainConditions.ino:47] testPowerDownDomainConditions(): Testing Condition 5: XTAL PD Domain
[  1227][E][ValidatePowerDownDomainConditions.ino:26] isError(): Configuration failed for XTAL: Error code: 0xFFFF
[  1238][E][ValidatePowerDownDomainConditions.ino:54] testPowerDownDomainConditions(): Condition 'XTAL PD Domain' failed.
[  1249][E][PowerDownDomainConditions.h:80] operator()(): Failed to configure 'XTAL' powerdown domain.

[  1259][D][ValidatePowerDownDomainConditions.ino:47] testPowerDownDomainConditions(): Testing Condition 6: VDDSDIO PD Domain
[  1270][E][ValidatePowerDownDomainConditions.ino:26] isError(): Configuration failed for VDDSDIO: Error code: 0xFFFF
[  1281][E][ValidatePowerDownDomainConditions.ino:54] testPowerDownDomainConditions(): Condition 'VDDSDIO PD Domain' failed.
[  1292][E][PowerDownDomainConditions.h:85] operator()(): Failed to configure 'VDDSDIO' powerdown domain.
```

#### **Analysis**
- **Result**:
  - All domains failed as expected, emulating error conditions.
- **Runtime**:
  - 252 ms (from first domain initialization to completion).
- **Conclusion**:
  - Error-handling logic successfully captured and logged all failures.
  - System behaves as intended under error conditions, providing clear diagnostics.
