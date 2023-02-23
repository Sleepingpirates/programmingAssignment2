#include <iostream>
#include <thread>
#include <atomic>
#include <random>
using namespace std;
const int N = 5; // Number of guests
atomic<int> guests_entered(0); // Atomic variable to keep track of guests entered
atomic<bool> new_cupcake(true); // Atomic variable to check if there is a new cupcake
atomic<bool> all_entered(false); // Atomic variable to check if all guests have entered
mt19937 rng(random_device{}()); // Random number generator
uniform_int_distribution<int> dist(0, 1); // Distribution for random number generator
mutex guests_entered_mutex; // Mutex to protect guests_entered

void guest(int id) {
    while (true) {
        //We lock the mutex to simulate the guests taking their time in the labyrinth
        guests_entered_mutex.lock(); // Acquire lock on guests_entered
        cout << "Guest " << id+1 << " is entering the labyrinth." << endl;
        if (new_cupcake.load()) { // Check if there is a new cupcake
            int decision = dist(rng); // Generate random number to decide whether to eat the cupcake or not
            if (decision == 0) {
                cout << "Guest " << id+1 << " is eating the cupcake." << endl;
                new_cupcake.store(false); // Eat the cupcake
            } else {
                cout << "Guest " << id+1 << " is leaving the cupcake." << endl;
            }
        } else {
            cout << "Guest " << id+1 << " is requesting a new cupcake... servants bring him a new cupcake." << endl;
            new_cupcake.store(true); // Request a new cupcake
            int decision = dist(rng); // Generate random number to decide whether to eat the new cupcake or not
            if (decision == 0) {
                cout << "Guest " << id+1 << " is eating the new cupcake." << endl;
                new_cupcake.store(false); // Eat the cupcake
            } else {
                cout << "Guest " << id+1 << " is leaving the new cupcake." << endl;
            }
        }
        guests_entered_mutex.unlock(); 
        break;
    }
}

void enterLabyrinth() {
    thread t[N];
    int entered[N] = {0}; // array to keep track of which guests have entered
    int count = 0; // count of guests that have entered at least once

    while (count < N) {
        // randomly select a guest
        int i = dist(rng, decltype(dist)::param_type{0, N-1});

        t[i] = thread(guest, i); // create thread for selected guest
        t[i].join(); // wait for thread to finish

        if (!entered[i]) { // check if guest has entered before
            entered[i] = 1; // mark guest as entered
            count++; // increment count of guests that have entered at least once
        }
        // Check if all guests have entered at least once
        bool all_entered = true;
        for (int j = 0; j < N; j++) {
            if (entered[j] == 0) {
                all_entered = false;
                break;
            }
        }
        if (all_entered) {
            cout << "All guests have entered the labyrinth." << endl;
            break;
        }
    }
    //pick a random guest to take the cake at the exit
    int i = dist(rng, decltype(dist)::param_type{0, N-1});
    cout << "Guest " << i+1 << " is taking the cake at the exit." << endl;
}


int main() {
    enterLabyrinth();
    return 0;
}
