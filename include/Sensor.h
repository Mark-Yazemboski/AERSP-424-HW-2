#ifndef SENSOR_H
#define SENSOR_H

#include <string>
using namespace std;


//Creates the Sensor class that has virtural functions for the gether data proccess data, and get type functions
class Sensor {
public:
    virtual ~Sensor() = default;
    virtual void gatherData() = 0;
    virtual void processData() = 0;
    virtual string get_Type() = 0;
};

#endif // SENSOR_H
