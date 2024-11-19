#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "Sensor.h"
#include <iostream>

//Creates the Temperature class, that can return its type, and say if its collecting or processing data
class Temperature_Sensor : public Sensor {
private:

public:
    string Type;
    Temperature_Sensor() {
        Type = "Temperature Sensor";
    }

    string get_Type() {
        return Type;
    }

    void gatherData() override {
        cout << "Gathering data from " << Type << endl;
    }

    void processData() override {
        cout << "Processing data from Temperature Sensor" << endl;
    }
};

#endif