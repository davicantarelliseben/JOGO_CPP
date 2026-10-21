#pragma once

typedef enum { BAU, FOGUEIRA } eventType;

class Event {
    private:
        eventType type;

    public:
        eventType getEventType();
        void triggerEvent(eventType type);
};