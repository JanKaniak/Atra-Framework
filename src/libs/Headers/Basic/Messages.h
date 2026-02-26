#pragma once
#include <string>

struct Message
{
private:
    std::string time_;
    std::string message_;

private:
    const std::string getTimeOfOccurence()
    {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%H:%M:%S", t);
        return std::string(buffer);
    }

public:
    Message(std::string message) : time_(getTimeOfOccurence()),message_(message) {}
    const std::string getTime() { return time_; }
    const std::string getMessage() { return message_; }
};