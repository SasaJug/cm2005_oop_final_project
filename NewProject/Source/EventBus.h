/*
  ==============================================================================

    EventBus.h
    Created: 25 Aug 2024 1:37:54pm
    Author:  Sasa Jugurdzija, with help from external examples.

  ==============================================================================
*/

#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class EventBus
{
public:
    using CallbackFunction = function<void(const string&)>;

    /**
     * @brief Gets the singleton instance of the EventBus.
     * @return EventBus& Reference to the singleton instance.
     */
    static EventBus& getInstance()
    {
        static EventBus instance;
        return instance;
    }

    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    /**
     * @brief Subscribes a callback function to an event type.
     * @param eventType The type of event to subscribe to.
     * @param callback The function to call when the event is triggered.
     */
    void subscribe(const string& eventType, CallbackFunction callback);

    /**
     * @brief Triggers an event, calling all subscribed callbacks.
     * @param eventType The type of event to trigger.
     * @param payload The data to pass to the callbacks.
     */
    void triggerEvent(const string& eventType, const string& payload);

private:
    EventBus() = default;

    unordered_map<string, vector<CallbackFunction>> listeners;
};
