/*
  ==============================================================================

    EventBus.cpp
    Created: 25 Aug 2024 1:37:54pm
    Author:  Sasa Jugurdzija, with help from external examples.

  ==============================================================================
*/

#include "EventBus.h"

void EventBus::subscribe(const string& eventType, CallbackFunction callback)
{
    listeners[eventType].push_back(callback);
}

void EventBus::triggerEvent(const string& eventType, const string& payload)
{
    if (listeners.find(eventType) != listeners.end())
    {
        for (auto& callback : listeners[eventType])
        {
            callback(payload);
        }
    }
}
