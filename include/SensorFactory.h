#ifndef SENSOR_FACTORY_H
#define SENSOR_FACTORY_H

#include "Sensor.h"

#include "AltitudeSensor.h"
#include "AirspeedSensor.h"
#include "TemperatureSensor.h"
#include <string>
#include <iostream>


//Creates the sensor factory class, this class will take in a string input, and will create
//A sensor based off of the input, and will return a pointer the the sensor object. It will also
//Print the memory location of the object, and the type of sensor it is.
class SensorFactory {
public:
    static Sensor* createSensor(const std::string& sensorType);
};

#endif
