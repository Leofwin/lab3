#pragma once

#include "diode.h"
#include "sensor.h"

#define DIODE_COLOR_RED 255
#define DIODE_COLOR_GREEN 0
#define DIODE_COLOR_BLUE 0

const float maxDistance = 20.0;

class Item {
public:
    Item(Diode* _diode, DistanceSensor* _sensor) {
        diode = _diode;
        sensor = _sensor;
    }

    activate() {
        diode->setColor(DIODE_COLOR_RED, DIODE_COLOR_GREEN, DIODE_COLOR_BLUE);
    }

    deactivate() {
        diode->turnOffColor();
    }

    bool wasHold() {
        return sensor->readDistance() <= maxDistance;
    }

private:
    DistanceSensor* sensor;
    Diode* diode;
};