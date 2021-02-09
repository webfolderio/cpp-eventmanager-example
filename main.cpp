#include <iostream>

#include "eventpp/eventdispatcher.h"
#include "eventpp/utilities/argumentadapter.h"

enum EventType {
    Start,
    Stop
};

class BaseEvent {

public:
    int field1;

    BaseEvent() {
        field1 = 1;
    }

    // Make the BaseEvent polymorphism so we can use dynamic_cast to detect
    // if it's a StartEvent or StopEvent
    virtual ~BaseEvent() {
    }
};

class StartEvent : public BaseEvent {
public:
    int field2;

    StartEvent() {
        field2 = 2;
    }
};

class StopEvent : public BaseEvent {

public:
    int field3;

    StopEvent() {
        field3 = 3;
    }
};

eventpp::EventDispatcher<EventType, void(const BaseEvent &)> dispatcher;

// adapted from: https://github.com/wqking/eventpp/blob/master/doc/argumentadapter.md
int main() {

    dispatcher.appendListener(
            EventType::Start,
            eventpp::argumentAdapter<void(const StartEvent &)>([](const StartEvent &e) {
                std::cout << "start event, field1: " << e.field1 << ", field2: " << e.field2 << std::endl;
            })
    );

    dispatcher.appendListener(
            EventType::Stop,
            eventpp::argumentAdapter<void(const StopEvent &)>([](const StopEvent &e) {
                std::cout << "stop event, field1: " << e.field1 << ", field3: " << e.field3 << std::endl;
            })
    );

    auto start = StartEvent{};
    dispatcher.dispatch(EventType::Start, start);

    auto stop = StopEvent{};
    dispatcher.dispatch(EventType::Stop, stop);

    return 0;
}
