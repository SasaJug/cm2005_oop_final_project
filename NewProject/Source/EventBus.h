/*
  ==============================================================================

    EventBus.h
    Created: 25 Aug 2024 1:37:54pm
    Author:  jugur

  ==============================================================================
*/

#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>

class EventBus
{
public:
    using CallbackFunction = std::function<void(const std::string&)>;

    // Public method to access the singleton instance
    static EventBus& getInstance()
    {
        static EventBus instance; // Guaranteed to be lazy-initialized and thread-safe in C++11 and later
        return instance;
    }

    // Prevent copying and assignment
    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    void subscribe(const std::string& eventType, CallbackFunction callback);
    void triggerEvent(const std::string& eventType, const std::string& payload);

private:
    // Private constructor to prevent instantiation
    EventBus() = default;

    std::unordered_map<std::string, std::vector<CallbackFunction>> listeners;
};

