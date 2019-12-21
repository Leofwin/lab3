#pragma once

#include "item.h"
#include "timer.h"

#define STATE_PAUSE 0
#define STATE_ACTIVE 1

#define MAX_ITEMS_COUNT 3

const int maxScoresPerRound = 5;
const long timeToHoldMs = 5L * 1000;
const long gameTimeMs = 20L * 1000;
const long NOT_ACTIVATED_DELAY = 1L * 1000;

const int MIN_PAUSE_DELAY = 1;
const int MAX_PAUSE_DELAY = 4;

class Game {
public:
    Game(Item** _items, int _itemsCount) {
        itemsCount = min(_itemsCount, MAX_ITEMS_COUNT);
        activeItemIndex = -1;
        for (int i = 0; i < itemsCount; i++) {
            items[i] = _items[i];
            items[i]->deactivate();
        }

        unsigned long currentTime = millis();
        roundTimer = new Timer(currentTime, getRandomDelayInMs());
        gameOverTimer = new Timer(currentTime, gameTimeMs);
        isDisposed = false;
        totalScores = 0;
        roundsCount = 0;
        currentState = STATE_PAUSE;
    }

    void tick() {
        if (isOver())
            return;

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

    int getScores() {
        return totalScores;
    }

    int getMaxScores() {
        return maxScoresPerRound * roundsCount;
    }

    void dispose() {
        if (isDisposed)
            return;
        
        for (int i = 0; i < itemsCount; i++)
            items[i]->deactivate();
        isDisposed = true;
    }

private:
    int itemsCount;
    int activeItemIndex;
    Item* items[MAX_ITEMS_COUNT];
    Timer* roundTimer;
    Timer* gameOverTimer;
    int currentState;
    bool isDisposed;
    int totalScores;
    int roundsCount;

    int getRandomDelayInMs() {
        return random(MIN_PAUSE_DELAY, MAX_PAUSE_DELAY + 1) * 1000;
    }

    void handlePause() {
        unsigned long currentTime = millis();
        if (!roundTimer->isOver(currentTime))
            return;

        int nextItemIndex = random(itemsCount + 1) - 1;
        if (!items[nextItemIndex]->isCanActivate()) {
            Serial.println("Hacking attempt!");
            roundsCount++;
            delay(NOT_ACTIVATED_DELAY);
            return;
        }

        items[nextItemIndex]->activate();
        activeItemIndex = nextItemIndex;
        roundTimer = new Timer(currentTime, timeToHoldMs);
        roundsCount++;
        currentState = STATE_ACTIVE;
    }

    void handleActive() {
        unsigned long currentTime = millis();
        Item* item = items[activeItemIndex];

        if (!roundTimer->isOver(currentTime) && !item->wasHold())
            return;

        totalScores += calculateScores(currentTime);
        item->deactivate();
        activeItemIndex = -1;
        roundTimer = new Timer(currentTime, getRandomDelayInMs());
        currentState = STATE_PAUSE;
    }

    int calculateScores(unsigned long currentTime) {
        if (roundTimer->isOver(currentTime))
            return 0;
        
        long delta = roundTimer->getDelta(currentTime);
        return maxScoresPerRound - (int)((double)delta / timeToHoldMs * maxScoresPerRound);
    }
};