#include "SensorFactory.h"
#include "AerospaceControlSystem.h"


//The main function will create three sensors and add then to the controler, then get the controler to monitor and adjust,
//Then kill the controler.
int main() {
    cout << "################## PROBLEM 01 #####################" << endl;
    auto ctrlSys = new AerospaceControlSystem();
    auto Temp_Sens = SensorFactory::createSensor("Temperature_Sensor");
    auto Alt_Sens = SensorFactory::createSensor("Altitude_Sensor");
    auto Speed_Sens = SensorFactory::createSensor("Airspeed_Sensor");

    if (Temp_Sens) ctrlSys->addSensor(Temp_Sens);
    if (Alt_Sens) ctrlSys->addSensor(Alt_Sens);
    if (Speed_Sens) ctrlSys->addSensor(Speed_Sens);

    ctrlSys->monitorAndAdjust();
    delete ctrlSys;
    cout << "################## END OF PROBLEM 01 #####################" << endl;
    return 0;
}
