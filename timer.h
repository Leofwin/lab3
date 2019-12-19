#pragma once

class Timer {
public:
    Timer(unsigned long _startTimeMs, long _duration) {
        startTimeMs = _startTimeMs;
        duration = _duration;
        isTimeOver = false;
    }

    long getDelta(unsigned long currentTime) {
        return currentTime - startTimeMs;
    }

    bool isOver(unsigned long currentTime) {
        if (isTimeOver)
            return true;

        long delta = getDelta(currentTime);
        isTimeOver = delta > duration;
        return isTimeOver;
    }

private:
    unsigned long startTimeMs;
    long duration;
    bool isTimeOver;
};