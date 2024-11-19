AERSP 424 HW#2

Question 5 


If a robot finishes a task and then is immediately assigned a new task, the robot may complete 
tasks forever. This means the robot will never put down the tools and the neighboring robots will 
never finish their tasks. In the dining philosopher problem this would be called starvation as some 
of the philosophers will never get to take a bite and therefore starve. A way to fix this would be to 
add a delay between a robot finishing its task and being assigned a new one. This would ensure that 
after a robot finishes its task, it will put the tools down so the neighboring robots can pick up the 
tools and finish their tasks. OR, you could have a flag/ boolean value that says weather its rotbot 1's turn or robot 2's turn. 