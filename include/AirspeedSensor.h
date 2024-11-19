#ifndef AIRSPEED_SENSOR_H
#define AIRSPEED_SENSOR_H

#include "Sensor.h"
#include <iostream>

//Creates the Airspeed class, that can return its type, and say if its collecting or processing data
class Airspeed_Sensor : public Sensor {
private:


    
public:
    string Type;
    Airspeed_Sensor() {
        Type = "Airspeed Sensor";
    }

    string get_Type() {
        return Type;
    }

    void gatherData() override {
        cout << "Gathering data from " << Type << endl;
    }

    void processData() override {
        cout << "Processing data from Airspeed Sensor" << endl;
    }
};

#endif