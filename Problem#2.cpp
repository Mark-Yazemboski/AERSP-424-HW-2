#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

//This creates a mutex array for the tools
mutex tools[5];

//This lets mutex protect the cout stream
mutex coutMutex;

//Function for each robot to perform its task
void robotTask(int id) {


    // Identify the two tools needed by this robot the tool to the left will be the same as the robot id, and the
    //tool to the right will be one more than the robot ID. The edge case is then robot ID 4 reaches to the right, 
    //That tool id would be 5, but really it should be tool zero, so we used (id + 1) % 5 which will make the 5 = 0
    int leftTool = id;
    int rightTool = (id + 1) % 5;

    //This will print if the robot is waiting for a tool and say what tools its waiting for.
    //also locks the thread so only one robot can print at a time
    {
        lock_guard<mutex> lock(coutMutex);
        cout << "Robot " << id << " reaching for tools " << leftTool << " and " << rightTool << "." << endl;
    }


    //Locks the tools that the current robot is using so the other robots cant break physics.
    tools[leftTool].lock();
    tools[rightTool].lock();

    //Prints when a robot has picked up the tools and is using them
    {
        lock_guard<mutex> lock(coutMutex);
        cout << "Robot " << id << " aquired tools " << leftTool << " and " << rightTool << " starts performing the task. " << endl;
    }

    //Simulates the robot doing the 5 second task
    this_thread::sleep_for(chrono::seconds(5));

    //Prints when the robot is done with the task and is putting the tools back down
    {
        lock_guard<mutex> lock(coutMutex);
        cout << "Robot " << id << " finished the task and is returning tools " << leftTool << " and " << rightTool << "." << endl;
    }

    //Unlocks the tools so other robots can use them
    tools[leftTool].unlock();
    tools[rightTool].unlock();
}


//Main will create the 5 robot threads, and will simulate them performing a task withthe 5 tools.
//It will also keep track of how long it takes all 5 robots to complete the task
int main() {
    cout<<"##################### Question 02 #######################"<<endl;

    //Gets the current time at the start
    auto start = chrono::high_resolution_clock::now();


    //Creates the threads for the robots
    vector<thread> robots;

    //This will create the different threads, and will assign them to run the robot task function with their respective IDS
    for (int i = 0; i < 5; ++i) {
        robots.push_back(thread(robotTask, i));
    }

    //Makes the threads wait till they are all done
    for (auto& robot : robots) {
        robot.join();
    }


    //Ends the timer
    auto end = chrono::high_resolution_clock::now();

    //Calculates the elapsed time and prints that we finished the problem
    chrono::duration<double> elapsed = end - start;
    cout << "All robots have completed their tasks." << endl;
    cout << "Total runtime: " << elapsed.count() << " seconds" << endl;
    cout<<"##################### End Question 02 #######################"<<endl;
    return 0;
}