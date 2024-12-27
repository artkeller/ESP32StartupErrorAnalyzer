/**
 * @file ErrorCounterWithDefault.ino
 * @brief Example usage of ESP32StartupErrorAnalyzer with NVS-based error counters and a default callback.
 *
 * This example demonstrates how to use the `ESP32StartupErrorAnalyzer` to track and count 
 * specific reset reasons, store counters persistently in NVS, and handle unknown errors with a default callback.
 */

#include <ESP32StartupErrorAnalyzer.h>
#include <Preferences.h>

// NVS storage for error counters
Preferences preferences;

static int panicResetCounter = 0;    ///< Counter for panic resets.
static int powerOnResetCounter = 0; ///< Counter for power-on resets.
static int unknownResetCounter = 0; ///< Counter for unknown resets.

/**
 * @brief Loads the error counters from NVS.
 */
void loadErrorCounters() {
    preferences.begin("errorCounters", true);
    panicResetCounter = preferences.getInt("panic", 0);
    powerOnResetCounter = preferences.getInt("poweron", 0);
    unknownResetCounter = preferences.getInt("unknown", 0);
    preferences.end();
}

/**
 * @brief Saves the error counters to NVS.
 */
void saveErrorCounters() {
    preferences.begin("errorCounters", false);
    preferences.putInt("panic", panicResetCounter);
    preferences.putInt("poweron", powerOnResetCounter);
    preferences.putInt("unknown", unknownResetCounter);
    preferences.end();
}

/**
 * @brief Defines startup conditions and their associated callbacks.
 *
 * @return A vector of `ErrorCondition` structures representing conditions and callbacks.
 */
std::vector<ESP32StartupErrorAnalyzer::ErrorCondition> getStartupConditions() {
    return {
        // Increment and report panic reset counter
        {[]() { return esp_reset_reason() == ESP_RST_PANIC; },
         []() {
             panicResetCounter++;
             Serial.printf("Panic reset detected! Counter: %d\n", panicResetCounter);
             saveErrorCounters();
         }},

        // Increment and report power-on reset counter
        {[]() { return esp_reset_reason() == ESP_RST_POWERON; },
         []() {
             powerOnResetCounter++;
             Serial.printf("Power-on reset detected! Counter: %d\n", powerOnResetCounter);
             saveErrorCounters();
         }},

        // Report external wakeup
        {[]() { return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0; },
         []() { Serial.println("Wakeup detected from external signal."); }}
    };
}

/**
 * @brief Sets up the ESP32 and initializes the startup error analyzer.
 *
 * The setup function initializes the serial connection, loads error counters from NVS,
 * configures the startup conditions, and adds a condition to reset counters on a brownout event.
 */
void setup() {
    // Initialize the serial connection
    Serial.begin(115200);
    while (!Serial) {};
    Serial.println("Firmware started: ESP32StartupErrorAnalyzer - ErrorCounterWithDefault");

    // Load counters from NVS
    loadErrorCounters();

    // Create the error analyzer with predefined startup conditions and a default callback
    ESP32StartupErrorAnalyzer analyzer(getStartupConditions(),
                                        []() { // Default callback: Increment and report unknown reset counter
                                            unknownResetCounter++;
                                            Serial.printf("Unknown error detected! Counter: %d\n", unknownResetCounter);
                                            saveErrorCounters();
                                        });

    // Add a condition to reset counters on brownout detection
    analyzer.addCondition(
        []() { return esp_reset_reason() == ESP_RST_BROWNOUT; },
        []() {
            panicResetCounter = 0;
            powerOnResetCounter = 0;
            unknownResetCounter = 0;
            saveErrorCounters();
            Serial.println("Brownout detected! All error counters reset.");
        });

    // Start analyzing conditions and execute corresponding callbacks
    Serial.println("Start Analyzer...");
    analyzer.analyze();  
    Serial.println("Ready!");
}

/**
 * @brief Main loop of the program.
 *
 * This function contains the primary logic of the program. In this example, it is left empty.
 */
void loop() {
    // Main logic
}
