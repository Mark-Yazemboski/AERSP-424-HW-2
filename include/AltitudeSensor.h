#ifndef ALTITUDE_SENSOR_H
#define ALTITUDE_SENSOR_H

#include "Sensor.h"
#include <iostream>

//Creates the Altitude class, that can return its type, and say if its collecting or processing data
class Altitude_Sensor : public Sensor {
private:

public:
    string Type;
    Altitude_Sensor() {
        Type = "Altitude Sensor";
    }

    string get_Type() {
        return Type;
    }

    void gatherData() override {
        cout << "Gathering data from " << Type << endl;
    }

    void processData() override {
        cout << "Processing data from Altitude Sensor" << endl;
    }
};

#endif