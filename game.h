#pragma once

#include "diode.h"
#include "sensor.h"
#include "timer.h"

#define MAX_ITEMS_COUNT 3
#define RED 255
#define GREEN 0
#define BLUE 0
const float maxDistance = 20.0;
const long timeToHoldMs = 1000 * 5;
const long gameTimeMs = 1000 * 40;

class Item {
public:
    Item(Diode* _diode, DistanceSensor* _sensor) {
        diode = _diode;
        sensor = _sensor;
    }

    activate() {
        diode->setColor(RED, GREEN, BLUE);
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

class Game {
public:
    Game(Item** _items, int _itemsCount) {
        itemsCount = _itemsCount > MAX_ITEMS_COUNT ? MAX_ITEMS_COUNT : _itemsCount;
        for (int i = 0; i < itemsCount; i++)
            items[i] = _items[i];
        timer = new Timer(0);
        gameOverTimer = new Timer(gameTimeMs);
    }

    void make_tact() {
        if (gameOverTimer->isOver())
            return;
    }

private:
    int itemsCount;
    Item* items[MAX_ITEMS_COUNT];
    Timer* timer;
    Timer* gameOverTimer;
};