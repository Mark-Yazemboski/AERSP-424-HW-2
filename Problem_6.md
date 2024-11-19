AERSP 424 HW#2

Question 6 

Some issues that arose during the development of the program 

If all the actions take time to complete, then a race condition may occur. If there is space in the 
traffic pattern and one plane arrives and tries to enter the pattern but it takes a moment to enter. 
Then another plane arrives and sees that there is space in the traffic pattern before the first plane 
enters the pattern, there will be two planes trying to enter the pattern when there is only one spot. 
The same problem can happen if it takes time for the ATC to wake up. One Pilot may start to wake 
up the ATC and a second pilot may see the ATC is still asleep and try to establish a connection. 
Having time in between actions is a solvable issue thought, you nee to use mutex, and keep 
variables from being modified by different threads at the same time. This was done in the program 
for #3 and is why it works so well.     