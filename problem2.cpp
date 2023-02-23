// Faiz Ahmed
// 02/23/2023
// The program allows guests to enter the showroom one at a time to view a vase.
// uses threads to simulate the guests.
// uses a mutex and a condition variable to control the access to the showroom.

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

using namespace std;

struct Showroom {
    const int N;
    queue<int> guests;
    bool busy = false;
    int count = 0;
    mutex m;
    condition_variable cv;

    Showroom(int n) : N(n) {}

    void guest(int id) {
        // Guest joins the queue
        {
            lock_guard<mutex> lock(m);
            guests.push(id);
        }
        // Guest waits until the showroom is not busy and there are guests waiting in the queue
        unique_lock<mutex> lock(m);
        cv.wait(lock, [this]() { return !busy && !guests.empty(); });
        guests.pop();
        busy = true;
        lock.unlock();

        // Guest enters the showroom and views the vase
        cout << "Guest " << id + 1 << " enters the showroom." << endl;
        this_thread::sleep_for(chrono::seconds(2));

        // Guest leaves the showroom
        lock_guard<mutex> lock2(m);
        if(count == N - 1)
            cout << "Guest " << id + 1 << " leaves." << endl;
        else
            cout << "Guest " << id + 1 << " leaves and tells the next guest to enter." << endl;
        busy = false;
        count++;

        // If all the guests have seen the vase, notify the waiting threads
        if (count == N) {
            cout << "All guests have seen the vase." << endl;
        }

        cv.notify_one();
    }
    // Method that runs the showroom simulation
    void run() {
        cout << N << " guests have arrived and joined the queue." << endl;
        // Spawn a thread for each guest
        for (int i = 0; i < N; i++) {
            thread t(&Showroom::guest, this, i);
            t.detach();
        }
        // Wait for all the guests to see the vase
        while (true) {
            lock_guard<mutex> lock(m);
            if (count == N) {
                break;
            }

            cv.notify_one();
        }
    }
};

int main() {
    //enter N guests to the showroom
    int N;
    cout << "Enter the number of guests: ";
    cin >> N;
    Showroom showroom(N);
    showroom.run();
    return 0;
}