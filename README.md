# Programming Assignment 2

## Problem 1: Minotaur's Birthday Party

The Minotaur invited N guests to his birthday party. When the guests arrived, he made
the following announcement.
The guests may enter his labyrinth, one at a time and only when he invites them to do
so. At the end of the labyrinth, the Minotaur placed a birthday cupcake on a plate. When
a guest finds a way out of the labyrinth, he or she may decide to eat the birthday
cupcake or leave it. If the cupcake is eaten by the previous guest, the next guest will find
the cupcake plate empty and may request another cupcake by asking the Minotaur’s
servants. When the servants bring a new cupcake the guest may decide to eat it or leave
it on the plate.
The Minotaur’s only request for each guest is to not talk to the other guests about her or
his visit to the labyrinth after the game has started. The guests are allowed to come up
with a strategy prior to the beginning of the game. There are many birthday cupcakes, so
the Minotaur may pick the same guests multiple times and ask them to enter the
labyrinth. Before the party is over, the Minotaur wants to know if all of his guests have
had the chance to enter his labyrinth. To do so, the guests must announce that they have
all visited the labyrinth at least once.
Now the guests must come up with a strategy to let the Minotaur know that every guest
entered the Minotaur’s labyrinth. It is known that there is already a birthday cupcake left
at the labyrinth’s exit at the start of the game. How would the guests do this and not
disappoint his generous and a bit temperamental host?
Create a program to simulate the winning strategy (protocol) where each guest is
represented by one running thread. In your program you can choose a concrete number
for N or ask the user to specify N at the start.

### Run Instructions.

1. Clone this repo

```
git clone https://github.com/Sleepingpirates/programmingAssignment2
```

2. Navigate to the location of the repo

```
cd programmingAssignment2
```

3. Compile the program:

```
g++ -std=c++11 -pthread  problem1.cpp -o pb1
```

4. Run the program:

```
./pb1
```

### Proof of Correctness

The solution guarantees that each guest has the opportunity to enter the labyrinth at least once, and that the Minotaur is informed when all guests have done so. This is achieved by creating N threads, one for each guest, and randomly selecting a guest to enter the labyrinth in each iteration of the main loop. Once a guest has entered the labyrinth, they check if there is a cupcake on the plate. If there is, they randomly decide whether to eat it or leave it. If they eat the cupcake, a flag is set to indicate that the cupcake has been eaten, so the next guest will request a new cupcake. If there is no cupcake, the guest requests a new one, and again randomly decides whether to eat it or leave it. Once all guests have entered the labyrinth at least once, we select a random guest to take the cupcake at the exit.

### Experimental Evaluation, Efficiency

The program uses threads to simulate the guests entering the labyrinth, which can lead to potential issues such as race conditions or deadlocks. To mitigate these issues, I used atomic variables to ensure that multiple threads can safely access shared data, and a mutex to protect the shared variable that keeps track of the number of guests that have entered the labyrinth. Overall, the program is efficient and effective in simulating the Minotaur's birthday party.

## Problem 2: Minotaur's Crystal Vase

The Minotaur decided to show his favorite crystal vase to his guests in a dedicated
showroom with a single door. He did not want many guests to gather around the vase
and accidentally break it. For this reason, he would allow only one guest at a time into
the showroom. He asked his guests to choose from one of three possible strategies for
viewing the Minotaur’s favorite crystal vase:

1. Any guest could stop by and check whether the showroom’s door is open at any time
   and try to enter the room. While this would allow the guests to roam around the castle
   and enjoy the party, this strategy may also cause large crowds of eager guests to gather
   around the door. A particular guest wanting to see the vase would also have no
   guarantee that she or he will be able to do so and when.
2. The Minotaur’s second strategy allowed the guests to place a sign on the door
   indicating when the showroom is available. The sign would read “AVAILABLE” or
   “BUSY.” Every guest is responsible to set the sign to “BUSY” when entering the
   showroom and back to “AVAILABLE” upon exit. That way guests would not bother trying
   to go to the showroom if it is not available.
3. The third strategy would allow the quests to line in a queue. Every guest exiting the
   room was responsible to notify the guest standing in front of the queue that the
   showroom is available. Guests were allowed to queue multiple times.
   Which of these three strategies should the guests choose? Please discuss the advantages
   and disadvantages.
   Implement the strategy/protocol of your choice where each guest is represented by 1
   running thread. You can choose a concrete number for the number of guests or ask the
   user to specify it at the start.

### Run Instructions.

1. Clone this repo

```
git clone https://github.com/Sleepingpirates/programmingAssignment2
```

2. Navigate to the location of the repo

```
cd programmingAssignment2
```

3. Compile the program:

```
g++ -std=c++11 -pthread  problem2.cpp -o pb2
```

4. Run the program:

```
./pb2
```

### Proof of Correctness

The program implements the third strategy where guests queue up and wait for their turn to enter the showroom. The correctness of the program can be shown by arguing that the following conditions are met:

At most one guest can access the showroom at a time: This is guaranteed by the use of a mutex lock and a condition variable. Only one guest can enter the showroom at a time and the rest are blocked until the previous guest leaves.

No guest is starved: Since guests are served in the order of arrival, no guest is left waiting indefinitely. Every guest gets a chance to enter the showroom.

All guests view the vase exactly once: The program keeps track of the number of guests that have viewed the vase using the count variable. When a guest leaves the showroom, the count is incremented. When the count equals the total number of guests, it means that all guests have viewed the vase.

Therefore, the program satisfies the requirements of the problem.

### Experimental Evaluation, Efficiency

In terms of efficiency, the implemented program allows guests to enter the showroom one at a time to view a vase, using threads to simulate the guests. The use of a mutex and a condition variable effectively controls the access to the showroom, ensuring that only one guest is present at any given time. The approach of having guests join a queue and wait for their turn to view the vase, as implemented in strategy #3, is the most efficient. Strategies 1 and 2 create contention around the door of the showroom, causing guests to waste cycles repeatedly trying to view the vase.
