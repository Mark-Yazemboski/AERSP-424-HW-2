#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <string>
#include <random>
using namespace std;
constexpr int MAX_TRAFFIC_PATTERN = 3;
constexpr int TOTAL_AIRCRAFT = 10;

//This will set all of the lists and multithreading variables we need for the problem

//This que represents the planes in the traffic pattern
queue<int> traffic_pattern; 

//Mutex variables that will only allow one thread to do stuff at a time
mutex mtx;                  
condition_variable cv;      

//Boolean value that represents if the ATC is sleeping
atomic<bool> atc_awake{false};

//Vector of wether the airplanes are tlaking to ATC
std::vector<bool> atc_talking(TOTAL_AIRCRAFT, false);

//Creates a vector that represents if the certain plane has landed yet
std::vector<bool> landed(TOTAL_AIRCRAFT, false);

//Mutex variable that is used at every print statment so they dont try printing at the same time.
mutex coutMutex;

//Chat GPT cooked this up, it is just a random number generator that will 
//Vary the interval that the planes arrive at.
void random_delay() {
    static random_device rd;  // Seed for the random number generator
    static mt19937 gen(rd()); // Mersenne Twister RNG
    static uniform_int_distribution<int> dist(0, 1300); // Range: 0 to 1300 ms

    int delay_ms = dist(gen); // Generate a random delay in milliseconds
    this_thread::sleep_for(chrono::milliseconds(delay_ms));
}


//This is the ATC function, this will have a thread dedicated to running it untill all planes are done.
//This will see if the pattern has a plane, and if so help land the plane, if there are no planes in
//The pattern the ATC will sleep
void airTrafficController() {

    //Runs till the thread is killed
    while (true) {

        //Locks everything for other threads till its done talking to the current plane thread
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !traffic_pattern.empty() || atc_awake.load(); });
        
        //If there is a plane in the pattern
        if (!traffic_pattern.empty()) {

            //Gets the planes ID from the front of the que
            int aircraft_id = traffic_pattern.front();
            
            //Sets the Aircraft talking array at the correct planes ID to true
            atc_talking[aircraft_id - 1] = true;
            
            

            //Says the plane is landing and simulates 1 second of landing time
            {
            lock_guard<mutex> lock(coutMutex);
            cout << "ATC talking to Aircraft " << aircraft_id << ". Landing in progress..." << endl;
            }


            //Unlocks the variables to the other threads
            lock.unlock();


            //Simulates the 1 second landing time
            this_thread::sleep_for(chrono::seconds(1)); 
           

            //Locks the mutex while its performing oporations on data
            lock.lock();

            //Releases the plane from the que
            traffic_pattern.pop();

            //Displays the current traffic pattern count
            {
            lock_guard<mutex> lock(coutMutex);
            cout << "Traffic pattern is now " << traffic_pattern.size() <<" / "<< MAX_TRAFFIC_PATTERN <<"."<<endl;
            }


            //Sets the talking array to false
            atc_talking[aircraft_id - 1] = false;

            //Assigns the planes index in the landed vector to true
            landed[aircraft_id - 1] = true;
        }

        //If the pattern is empty, the ATC will sleep
        if (traffic_pattern.empty()) {
            {
            lock_guard<mutex> lock(coutMutex);
            std::cout << "ATC is falling asleep." << endl;
            }

            //Sets the awake to false
            atc_awake.store(false);
        }

        //Unlocks everything and tells the threads to update
        lock.unlock();
        cv.notify_all();
    }
}

//This function will be handeled by the planes, it will see if the ATC is sleeping and will wake them
//Up if they are, it will algo check to see if the traffic pattern is full, if so it will go away and
//probably crash from lack of fuel,
void pilot(int id) {

    //Stops other threads from messing with the data while it does these checks
    unique_lock<mutex> lock(mtx);

    //Notifies everyone its aproching
    {
    lock_guard<mutex> lock(coutMutex);
    cout << "Aircraft " << id << " approaching."<<endl;
    }


    //Checks to see if the pattern is full, if so it will go somewhere else
    if (traffic_pattern.size() >= MAX_TRAFFIC_PATTERN) {
        {
        lock_guard<mutex> lock(coutMutex);
        cout << "Aircraft " << id << " diverting to another airport. Traffic pattern full."<<endl;
        cout<<endl;
        }
        return;
    }

    //If the ATC isn't doing its job it will wake him up
    if (!atc_awake.load()) {
        {
        lock_guard<mutex> lock(coutMutex);
        cout << "Aircraft " << id << " wakes up ATC."<<endl;
        }

        //Sets awake to true
        atc_awake.store(true);
    }

    //If the pattern wasn;t full, it will add itsself to the pattern
    traffic_pattern.push(id);
    {
    lock_guard<mutex> lock(coutMutex);
    cout << "Aircraft " << id << " enters the traffic pattern."<<endl;
    }

    //Says how full the pattern is
    {
    lock_guard<mutex> lock(coutMutex);
    cout << "Traffic pattern is now " << traffic_pattern.size() <<" / "<< MAX_TRAFFIC_PATTERN <<"."<<endl;
    cout<<endl;
    }

    //Unlocks the data structures, and notofies the other threads to recheck them
    lock.unlock();
    cv.notify_all();
    
    //This will run untill the ATC talks to the plane.
    while (!atc_talking[id - 1]) {
        this_thread::yield(); 
    }

    //Prints that the plane is beginning the landing
    {
    lock_guard<mutex> lock(coutMutex);
    cout << "Ladies and gentalmen, this is your capain speaking, plane " << id << " is now landing." <<endl;
    }

    //Waits till the ATC designates the plane landed before continueing
    while (!landed[id - 1]) {
        this_thread::yield(); 
    }

    //Prints that the plane landed
    {
    lock_guard<mutex> lock(coutMutex);
    cout << "Applause errupts from plane " << id << " as the pilot butters the landing." <<endl;
    cout<<endl;
    }

}

int main() {
    cout<<"####################### Problem 03 ###########################" <<endl;
    //Creates the ATC thread
    thread atc_thread(airTrafficController);

    //Creates a vector of pilots
    vector<thread> pilots;

    //Goes throough and creates the pilots, and tells then to run the pilot function with a certain id
    for (int i = 1; i <= TOTAL_AIRCRAFT; ++i) {
        pilots.emplace_back(pilot, i);

        //Sets a random delay till the next plane comes in
        random_delay(); 
    }


    //Waits for all of the pilots to be done
    for (auto& p : pilots) {
        p.join();
    }

    //Kills the ATC person (he is "asleep")
    atc_thread.detach();
    cout<<"The airport is now quiet"<<endl;

    cout<<"####################### End of Problem 03 ###########################" <<endl;
    return 0;
}