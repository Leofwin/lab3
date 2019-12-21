#include "diode.h"
#include "sensor.h"
#include "game.h"
#include "printer.h"

#define R_OUT_FIRST 7
#define G_OUT_FIRST 8
#define B_OUT_FIRST 9

#define R_OUT_SECOND 7
#define G_OUT_SECOND 8
#define B_OUT_SECOND 9

#define R_OUT_THIRD 7
#define G_OUT_THIRD 8
#define B_OUT_THIRD 9

const int sensorPinFirst = A0;
const int sensorPinSecond = A1;
const int sensorPinThird = A2;

const int dinPin = 26;
const int clkPin = 22;
const int csPin = 24;
const int displayCount = 1;
ScorePrinter* scorePrinter;
Game* game;
bool isPrintScores = false;

void setup() {
    const Item* items[] = {
        new Item(new Diode(R_OUT_FIRST, G_OUT_FIRST, B_OUT_FIRST), new DistanceSensor(sensorPinFirst)),
        new Item(new Diode(R_OUT_SECOND, G_OUT_SECOND, B_OUT_SECOND), new DistanceSensor(sensorPinSecond)),
        new Item(new Diode(R_OUT_THIRD, G_OUT_THIRD, B_OUT_THIRD), new DistanceSensor(sensorPinThird))
    };
    game = new Game(items, 3);
    scorePrinter = new ScorePrinter(dinPin, clkPin, csPin, displayCount);
}

void loop() {
    if (isPrintScores)
        return;

    if (!game->isOver()) {
        game->tick();
    }

    scorePrinter->printScores(game->getScores(), game->getMaxScores());
    isPrintScores = true;
}
