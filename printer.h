#pragma once

#include "LedControl.h"

#define WIDTH 8
#define CELLS_COUNT 64
#define DRAW_DELAY 100

class ScorePrinter {
public:
    ScorePrinter(int dinPin, int clkPin, int csPin, int displayCount = 1) {
        ledDisplay = new LedControl(dinPin, clkPin, csPin, displayCount);
    }

    initialize() {
        ledDisplay->shutdown(0, false);
        ledDisplay->setIntensity(0, 10);
        ledDisplay->clearDisplay(0);
    }

    printScores(int scores, int maxScores) {
        const int cellsCount = scores * CELLS_COUNT / maxScores;

        for (int i = 0; i < cellsCount; i++) {
            int y = i / WIDTH;
            int x = i % WIDTH;
            drawPoint(y, x);
            delay(DRAW_DELAY);
        }
    }

private:
    LedControl* ledDisplay;

    drawPoint(int y, int x) {
        ledDisplay->setLed(0, y, x, true);
    }
};