#ifndef ESP32STARTUPERRORANALYZER_H
#define ESP32STARTUPERRORANALYZER_H

#include <functional>
#include <vector>

class ESP32StartupErrorAnalyzer {
public:
    using Condition = std::function<bool()>;
    using Callback = std::function<void()>;

    struct ErrorCondition {
        Condition condition;
        Callback callback;
    };

    ESP32StartupErrorAnalyzer(const std::vector<ErrorCondition>& conditions, Callback defaultCallback = nullptr);
    void analyze();
    void addCondition(const Condition& condition, const Callback& callback);

private:
    std::vector<ErrorCondition> conditions_;
    Callback defaultCallback_;
};

#endif
