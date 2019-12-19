#pragma once

#include "diode.h"
#include "sensor.h"
#include "timer.h"

#define STATE_PAUSE 0
#define STATE_ACTIVE 1

#define MAX_ITEMS_COUNT 3

#define DIODE_COLOR_RED 255
#define DIODE_COLOR_GREEN 0
#define DIODE_COLOR_BLUE 0

const float maxDistance = 20.0;
const long timeToHoldMs = 1000 * 5;
const long gameTimeMs = 1000 * 40;

const int MIN_PAUSE_DELAY = 1;
const int MAX_PAUSE_DELAY = 4;

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

class Game {
public:
    Game(Item** _items, int _itemsCount) {
        itemsCount = _itemsCount > MAX_ITEMS_COUNT ? MAX_ITEMS_COUNT : _itemsCount;
        activeItemIndex = -1;
        for (int i = 0; i < itemsCount; i++)
            items[i] = _items[i];

        unsigned long currentTime = millis();
        timer = new Timer(currentTime, getRandomDelay());
        gameOverTimer = new Timer(currentTime, gameTimeMs);
        isDisposed = false;
        totalScores = 0;
    }

    void tick() {
        if (isOver()) {
            dispose();
            return;
        }

        switch (currentState)
        {
            case STATE_PAUSE:
                handlePause();
                break;

            case STATE_ACTIVE:
                handleActive();
                break;
        
            default:
                break;
        }
    }

    bool isOver() {
        return gameOverTimer->isOver(millis());
    }

    int getTotalScores() {
        return totalScores;
    }

private:
    int itemsCount;
    int activeItemIndex;
    Item* items[MAX_ITEMS_COUNT];
    Timer* timer;
    Timer* gameOverTimer;
    int currentState;
    bool isDisposed;
    int totalScores;

    long getRandomDelay() {
        return (long)random(MIN_PAUSE_DELAY, MAX_PAUSE_DELAY + 1) * 1000;
    }

    void handlePause() {
        unsigned long currentTime = millis();
        if (!timer->isOver(currentTime))
            return;

        activeItemIndex = random(0, itemsCount);
        items[activeItemIndex]->activate();
        timer = new Timer(currentTime, timeToHoldMs);
        currentState = STATE_ACTIVE;
    }

    void handleActive() {
        unsigned long currentTime = millis();
        Item* item = items[activeItemIndex];

        if (!timer->isOver(currentTime) && !item->wasHold())
            return;

        totalScores += calculateScores(currentTime);
        item->deactivate();
        activeItemIndex = -1;
        timer = new Timer(currentTime, getRandomDelay());
        currentState = STATE_PAUSE;
    }

    void dispose() {
        if (isDisposed)
            return;
        
        if (activeItemIndex > 0)
            items[activeItemIndex]->deactivate();
        isDisposed = true;
    }

    int calculateScores(unsigned long currentTime) {
        if (timer->isOver(currentTime))
            return 0;
        
        long delta = timer->getDelta(currentTime);
        // todo: make normal calculation
        return 1;
    }
};