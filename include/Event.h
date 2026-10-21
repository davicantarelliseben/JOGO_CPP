#pragma once

typedef enum {/*...*/} eventType;

class Event {
    private:
        eventType type;

    public:
        eventType getEventType();
        void triggerEvent(eventType type);
};