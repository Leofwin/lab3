#include "diode.h"
#include "sensor.h"
#include "game.h"
#include "printer.h"

ScorePrinter* scorePrinter;
Game* game;
bool isPrintScores = false;

void setup() {
    Serial.begin(115200);
    const GameController* controllers[] = {
        new GameController(new Diode(45, 47, 49), new DistanceSensor(A0)),
        new GameController(new Diode(44, 46, 48), new DistanceSensor(A3)),
        new GameController(new Diode(35, 37, 39), new DistanceSensor(A5))
    };
    game = new Game(controllers, 3);
    scorePrinter = new ScorePrinter(26, 22, 24, 1);
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
