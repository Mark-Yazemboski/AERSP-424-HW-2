#include "SensorFactory.h"


//Creates the sensor factory class, this class will take in a string input, and will create
//A sensor based off of the input, and will return a pointer the the sensor object. It will also
//Print the memory location of the object, and the type of sensor it is.
Sensor* SensorFactory::createSensor(const std::string& sensorType) {
    Sensor* sensor = nullptr;

    if (sensorType == "Temperature_Sensor") {
        sensor = new Temperature_Sensor();
    }
    else if (sensorType == "Altitude_Sensor") {
        sensor = new Altitude_Sensor();
    }
    else if (sensorType == "Airspeed_Sensor") {
        sensor = new Airspeed_Sensor();
    }
    else {
        std::cout << "Invalid Sensor Type" << std::endl;
        return nullptr;
    }

    std::cout << "Sensor created at " << sensor << " of type " << sensor->get_Type() << std::endl;
    return sensor;
}
