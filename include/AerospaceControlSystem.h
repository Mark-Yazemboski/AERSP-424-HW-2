#ifndef AEROSPACE_CONTROL_SYSTEM_H
#define AEROSPACE_CONTROL_SYSTEM_H

#include "Sensor.h"
#include <vector>
#include <iostream>

class AerospaceControlSystem {
private:
    std::vector<Sensor*> Sensors;

public:
    ~AerospaceControlSystem(); 
    void addSensor(Sensor* Sensor); 
    void monitorAndAdjust(); 
};

#endif // AEROSPACE_CONTROL_SYSTEM_H
