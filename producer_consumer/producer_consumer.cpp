#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <string>

using namespace std;

const int max_size = 10;
queue<int> q;
condition_variable cv_producer;
condition_variable cv_consumer;
mutex m;
int product = 0;

void producer(string name) {
    while (true) {
        // this_thread::sleep_for(chrono::milliseconds(100));
        unique_lock<mutex> lk(m);
        cv_producer.wait(lk, []{ return q.size() != max_size; });
        cout << "producer[" << name << "] -> " << product
             << ", size: " << q.size() << '\n';
        q.push(product++);
        cv_consumer.notify_all();
    }
}

void consumer(string name) {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(500));
        unique_lock<mutex> lk(m);
        cv_consumer.wait(lk, []{ return !q.empty(); });

        int p_id = q.front();
        cout << "consumer[" << name << "] <- " << p_id
             << ", size: " << q.size() << '\n';
        q.pop();
        cv_producer.notify_all();
    }
}

int main() {
    vector<thread> producers, consumers;
    int n_producer = 2;
    int n_consumer = 10;
    for (int i = 0; i < n_producer; i++) {
        producers.emplace_back(producer, "P_" + to_string(i));
    }

    for (int i = 0; i < n_consumer; i++) {
        consumers.emplace_back(consumer, "C_" + to_string(i));
    }

    for (int i = 0; i < n_producer; i++) {
        producers[i].join();
    }

    for (int i = 0; i < n_consumer; i++) {
        consumers[i].join();
    }
}
