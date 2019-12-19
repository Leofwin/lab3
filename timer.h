#pragma once

class Timer {
public:
    Timer(long _duration) {
        startTimeMs = millis();
        duration = _duration;
        isTimeOver = false;
    }

    long getDelta() {
        return millis() - startTimeMs;
    }

    bool isOver() {
        if (isTimeOver)
            return true;

        long delta = getDelta();
        isTimeOver = delta > duration;
        return isTimeOver;
    }

private:
    unsigned long startTimeMs;
    long duration;
    bool isTimeOver;
};