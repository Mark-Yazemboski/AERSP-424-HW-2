#include <iostream>
#include <vector>
#include <memory>
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
        cout << "Gathering data from " << Type <<endl;
    }

    void processData() override {
        cout << "Processing data from Temperature Sensor"<<endl;
    }
};


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
        cout << "Gathering data from " << Type <<endl;
    }

    void processData() override {
        cout << "Processing data from Altitude Sensor"<<endl;
    }
};

class Airspeed_Sensor : public Sensor {
private:


//Creates the Airspeed class, that can return its type, and say if its collecting or processing data
public:
    string Type;
    Airspeed_Sensor() {
        Type = "Airspeed Sensor";
    }

    string get_Type() {
        return Type;
    }

    void gatherData() override {
        cout << "Gathering data from " << Type <<endl;
    }

    void processData() override {
        cout << "Processing data from Airspeed Sensor"<<endl;
    }
};


//Creates the sensor factory class, this class will take in a string input, and will create
//A sensor based off of the input, and will return a pointer the the sensor object. It will also
//Print the memory location of the object, and the type of sensor it is.
class SensorFactory {
public:
   
    static Sensor* createSensor(const string& sensorType) {
        Sensor* sensor = nullptr;
        if (sensorType == "Temperature_Sensor") {
            sensor = new Temperature_Sensor();
        } else if (sensorType == "Altitude_Sensor") {
            sensor = new Altitude_Sensor();
        } else if (sensorType == "Airspeed_Sensor"){
            sensor = new Airspeed_Sensor();
        } else{
            cout<<"Invalid Sensor Type"<<endl;
            return nullptr; 
        }
        cout<<"Sensor created " << &sensor << " of type " << sensor->get_Type()<<endl;
        return sensor;

        
    }
};

//This class will keep track of all of the sensors it controls. It will have a function 
//Called add sensor, which will add a sensor object to its list of sensor,
//And also amonitor and adjust function that will collect and process all of the data from every sensor 
class AerospaceControlSystem {
private:
    vector<Sensor*> Sensors;

public:

    //When the AerospaceControlSystem object is destroyed, this will kill all of the sensors it holds.
    //This is important because we dont want these sensors using up more memory than needed if they will never be called again.
    ~AerospaceControlSystem() {
        for (auto Sensor : Sensors) {
            cout<<"Sensor deleted " << &Sensor << " of type " << Sensor->get_Type()<<endl;
            delete Sensor;
        }
    }

    //This will add a sensor to the list of sensors the control system holds
    void addSensor(Sensor* Sensor) {
        Sensors.push_back(Sensor);
    }

    //this will iterate through the sensor list and call gether data and proccess data on all of the sensor objects
    void monitorAndAdjust() {
        for (auto Sensor : Sensors) {
            Sensor->gatherData();
            Sensor->processData();
            cout << "Adjusting controls based on sensor data." << endl;
        }
    }
};



//The main function will create three sensors and add then to the controler, then get the controler to monitor and adjust,
//Then kill the controler.
int main() {
    cout << "##################### QUESTION 01 #########################" << endl;
    auto ctrlSys = new AerospaceControlSystem();
    auto Factory = new SensorFactory();
    auto Temp_Sens = Factory->createSensor("Temperature_Sensor");
    auto Alt_Sens = Factory->createSensor("Altitude_Sensor");
    auto Speed_Sens = Factory->createSensor("Airspeed_Sensor");
    ctrlSys->addSensor(Temp_Sens);
    ctrlSys->addSensor(Alt_Sens);
    ctrlSys->addSensor(Speed_Sens);
    ctrlSys->monitorAndAdjust();
    delete ctrlSys;
    cout << "##################### END QUESTION 01 #########################" << endl;
    return 1;
}