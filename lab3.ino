#include "diode.h"
#include "sensor.h"
#include "game.h"
#include "printer.h"
#include "LedControl.h"

#define R_OUT_FIRST 45
#define G_OUT_FIRST 47
#define B_OUT_FIRST 49

#define R_OUT_SECOND 44
#define G_OUT_SECOND 46
#define B_OUT_SECOND 48

#define R_OUT_THIRD 35
#define G_OUT_THIRD 37
#define B_OUT_THIRD 39

const int sensorPinFirst = A0;
const int sensorPinSecond = A3;
const int sensorPinThird = A5;

const int dinPin = 26;
const int clkPin = 22;
const int csPin = 24;
const int displayCount = 1;
ScorePrinter* scorePrinter;
Game* game;
bool isPrintScores = false;

void setup() {
    Serial.begin(115200);
    const Item* items[] = {
        new Item(new Diode(R_OUT_FIRST, G_OUT_FIRST, B_OUT_FIRST), new DistanceSensor(sensorPinFirst)),
        new Item(new Diode(R_OUT_SECOND, G_OUT_SECOND, B_OUT_SECOND), new DistanceSensor(sensorPinSecond)),
        new Item(new Diode(R_OUT_THIRD, G_OUT_THIRD, B_OUT_THIRD), new DistanceSensor(sensorPinThird))
    };
    game = new Game(items, 3);
    scorePrinter = new ScorePrinter(dinPin, clkPin, csPin, displayCount);
    scorePrinter->initialize();
    Serial.println("Game has began!");
}

void loop() {
    if (isPrintScores)
        return;

    if (!game->isOver()) {
        game->tick();
        return;
    }

    game->dispose();
    Serial.println("Game over!");
    Serial.print("Your scores is ");
    Serial.print(game->getScores());
    Serial.print(" of ");
    Serial.print(game->getMaxScores());
    Serial.println();
    scorePrinter->printScores(game->getScores(), game->getMaxScores());
    isPrintScores = true;
}
