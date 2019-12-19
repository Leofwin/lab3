#pragma once

class Diode {
public:
    Diode(int _pinRed, int _pinGreen, int _pinBlue) {
        pinRed = _pinRed;
        pinBlue = _pinBlue;
        pinGreen = _pinGreen;

        pinMode(pinRed, OUTPUT);
        pinMode(pinGreen, OUTPUT);
        pinMode(pinBlue, OUTPUT);
    }

    void setColor(int red, int blue, int green) {
        analogWrite(pinRed, 255 - red);
        analogWrite(pinGreen, 255 - green);
        analogWrite(pinBlue, 255 - blue);
    }

    void turnOffColor() {
        setColor(0, 0, 0);
    }

private:
    int pinRed;
    int pinBlue;
    int pinGreen;
};