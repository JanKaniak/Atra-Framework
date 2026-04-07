#pragma once
#include <string>

struct Message
{
private:
    struct tm *time_;
    std::string message_;

private:
    const void getTimeOfOccurence()
    {
        time_t now = time(NULL);
        time_ = localtime(&now);
    }

public:
    Message(std::string message) : message_(message) {
        getTimeOfOccurence();
    }
    const tm *getTime() { return time_; }
    const std::string getTimeString()
    {
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%H:%M:%S", time_);
        return std::string(buffer);
    }
    const std::string getMessage() { return message_; }
};