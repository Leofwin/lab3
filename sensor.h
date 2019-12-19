#pragma once

class DistanceSensor {
public:
    DistanceSensor(int _pin) {
        pin = _pin;
        voltsPerMeasurement = 5.0/1024.0;
    }

    float readDistance() {
        float volts = readAnalog() * voltsPerMeasurement;
        return pow(14.7737/volts, 1.2134);
    }

private:
    int pin;
    float voltsPerMeasurement;

    float readAnalog() {
        int sum = 0;
        int maxV = -5000;
        int minV = 5000;
        int n = 15;
        for (int i = 0; i < n; i++)
        {
            int cur = analogRead(pin);
            if (cur > maxV)
                maxV = cur;
            if (cur < minV)
                minV = cur;
            sum += cur;
            delay(6);
        }
        return (sum - maxV - minV) / (float)(n - 2);
    }
};