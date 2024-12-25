#ifndef STARTUP_ERROR_ANALYZER_H
#define STARTUP_ERROR_ANALYZER_H

#include <functional>
#include <vector>

class StartupErrorAnalyzer {
public:
    using Condition = std::function<bool()>;
    using Callback = std::function<void()>;

    struct ErrorCondition {
        Condition condition;
        Callback callback;
    };

    // Konstruktor: Default-Callback ist optional
    StartupErrorAnalyzer(const std::vector<ErrorCondition>& conditions, Callback defaultCallback = nullptr);

    // Fuehre die Analyse durch
    void analyze();

    // Dynamisches Hinzufügen weiterer Bedingungen
    void addCondition(const Condition& condition, const Callback& callback);

private:
    std::vector<ErrorCondition> conditions_;
    Callback defaultCallback_;
};

#endif // STARTUP_ERROR_ANALYZER_H
