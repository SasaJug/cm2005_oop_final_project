/*
  ==============================================================================

    EventBus.cpp
    Created: 25 Aug 2024 1:37:54pm
    Author:  jugur

  ==============================================================================
*/
#include "EventBus.h"

// Subscribe to an event by adding the callback function to the list for that event.
void EventBus::subscribe(const std::string& eventType, CallbackFunction callback)
{
    listeners[eventType].push_back(callback);
}

// Trigger the event by calling each registered callback for the event type.
void EventBus::triggerEvent(const std::string& eventType, const std::string& payload)
{
    if (listeners.find(eventType) != listeners.end())
    {
        for (auto& callback : listeners[eventType])
        {
            callback(payload);  // Call the callback with the payload
        }
    }
}


