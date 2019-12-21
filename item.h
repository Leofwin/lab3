#pragma once

#include "diode.h"
#include "sensor.h"

#define DIODE_COLOR_RED 255
#define DIODE_COLOR_GREEN 0
#define DIODE_COLOR_BLUE 0

const float MAX_POTENTIAL_DISTANCE = 200.0;
const float maxDistance = 25.0;

class GameController {
public:
    GameController(Diode* _diode, DistanceSensor* _sensor) {
        diode = _diode;
        sensor = _sensor;
    }

    isCanActivate() {
        float distance = sensor->readDistance();
        return distance > maxDistance && distance <= MAX_POTENTIAL_DISTANCE;
    }

    activate() {
        diode->setColor(DIODE_COLOR_RED, DIODE_COLOR_GREEN, DIODE_COLOR_BLUE);
    }

    deactivate() {
        diode->turnOffColor();
    }

    bool wasHold() {
        return sensor->readDistance() < maxDistance;
    }

private:
    DistanceSensor* sensor;
    Diode* diode;
};