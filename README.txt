Question1

* Compile the three included C-files:
	1. q1_CI.c
	2. q1_ST.c
	3. q1_TA.c

use:
	gcc q1_CI.c -o CI
	gcc q1_ST.c -o ST
	gcc q1_TA.c -o TA

* Run the Executable Files in seperate Windows of Terminal:
	./CI
	./ST
	./TA

* In q1_CI program, the User is prompted to enter the Marks for 5 Students (in range 0-50)
* Message Queues will carry Data From One process to Another and Corresponding Outputs are Displayed

* Each Student will Recieve their Marks (via message queue and Message Type = the ID of the Student)
* TA will Calculate the Average and Grades and send to CI (via message queue)
* CI will print the Average and Grades

---------------------------------------------------------------

Question2

* Compile the included C-File:
	1. q2.c

use: 
	gcc q2.c

* Run the Executable file as:
	./a.out

* Input is Read from the sample_input1 file (not through Terminal) provided in the Folder

Format of Input (linewise):
	Number of Processes
	Number of Resources
	AllocTable
	MaxTable
	Total number of instances per resource type.

Query Format:
	a = Ouput a Safe Sequence
	b = Check if a Given Sequence is Safe
	c = Check if a Request of Resources can be Granted
	t = terminate

Example Input File and Query:
5
3
10 5 7
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
7 5 3
3 2 2
9 0 2
4 2 2
5 3 3
a
b
1 2 3 4 5
b
2 3 1 4 5
c
7 7 7
c
1 0 2
c
1 0 0
t

---------------------------------------------------------------------------

Question3

* Compile and Run the Included C-File as:
	gcc q3.c
	./a.out

* Logs for each Philosopher's Current Activity/Status (THINKING, HUNGRY, EATING, took Fork 1, etc....)

* Press Control C to Exit


