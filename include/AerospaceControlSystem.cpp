#include "AerospaceControlSystem.h"

AerospaceControlSystem::~AerospaceControlSystem() {
    for (auto Sensor : Sensors) {
        std::cout << "Sensor deleted at " << Sensor << " of type " << Sensor->get_Type() << std::endl;
        delete Sensor;
    }
}

void AerospaceControlSystem::addSensor(Sensor* Sensor) {
    Sensors.push_back(Sensor);
}

void AerospaceControlSystem::monitorAndAdjust() {
    for (auto Sensor : Sensors) {
        Sensor->gatherData();
        Sensor->processData();
        std::cout << "Adjusting controls based on sensor data." << std::endl;
    }
}
