#include <cassert>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

int meals = 0;

int myrand(int min, int max) {
    static std::mt19937 rnd(time(nullptr));
    return std::uniform_int_distribution<>(min, max)(rnd);
}

void philosopher(int ph, std::mutex& ma, std::mutex& mb, std::mutex& mo) {
    for (int i = 0; i < meals; i++) {
        int duration = myrand(200, 800);
        {
            std::lock_guard<std::mutex> gmo(mo);
            std::cout << ph << " thinks " << duration << "ms\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
        {
            std::lock_guard<std::mutex> gmo(mo);
            std::cout << "\t\t" << ph << " is hungry\n";
        }
        std::lock_guard<std::mutex> gma(ma);
        std::lock_guard<std::mutex> gmb(mb);
        duration = myrand(200, 800);
        {
            std::lock_guard<std::mutex> gmo(mo);
            std::cout << "\t\t\t\t" << ph << " eats " << i + 1 << " meal "
                      << duration << "ms\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    }
}

int main(int argc, char* argv[]) {
    assert(argc > 2);

    const int phil_num = std::atoi(argv[1]);
    meals = std::atoi(argv[2]);
    assert(phil_num > 1);
    assert(meals > 0);
    std::vector<std::mutex> mutex_vect(phil_num);
    std::vector<std::thread> thread_vect{};
    std::mutex mo;

    for (int i = 0; i < phil_num; i++) {
        thread_vect.emplace_back([&mutex_vect, i, phil_num, &mo] {
            philosopher(i + 1, mutex_vect.at(i),
                        mutex_vect.at((i + 1) % phil_num), mo);
        });
    }

    for (int i = 0; i < phil_num; i++) {
        thread_vect.at(i).join();
    }
}
