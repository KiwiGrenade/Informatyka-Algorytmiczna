#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <semaphore>
#include <thread>

constexpr const size_t N = 5;  // number of philosophers (and forks)
enum class State 
{
    THINKING = 0,  // philosopher is THINKING
    HUNGRY = 1,    // philosopher is trying to get forks
    EATING = 2,    // philosopher is EATING
};

std::mutex critical_region_mtx;  // mutual exclusion for critical regions for 
// (picking up and putting down the forks)
std::mutex output_mtx;  // for synchronized cout (printing THINKING/HUNGRY/EATING status)

// array of binary semaphors, one semaphore per philosopher.
// Acquired semaphore means philosopher i has acquired (blocked) two forks
// std::binary_semaphore both_forks_available[N]
// {
//     std::binary_semaphore{0}, std::binary_semaphore{0},
//     std::binary_semaphore{0}, std::binary_semaphore{0},
//     std::binary_semaphore{0}
// };

size_t my_rand(size_t min, size_t max) 
{
    static std::mt19937 rnd(std::time(nullptr));
    return std::uniform_int_distribution<>(min, max)(rnd);
}


class Philosopher { 
    State state;
    Philosopher* left = nullptr;
    Philosopher* right = nullptr;
    size_t id;
    size_t toEat = 0;
    std::binary_semaphore both_forks{0};

    // FIXME: SEGFAULT HERE!!!
    static void test(Philosopher* p)
    // if philosopher i is hungry and both neighbours are not eating then eat
    { 
        // i: philosopher number, from 0 to N-1
        if (p->state == State::HUNGRY &&
            p->left->state != State::EATING &&
            p->right->state != State::EATING )
        {
            p->state = State::EATING;
            p->both_forks.release(); // forks are no longer needed for this eat session
        }
    }

    void think() 
    {
        size_t duration = my_rand(400, 800);
        {
            std::lock_guard<std::mutex> lk(output_mtx); // critical section for uninterrupted print
            std::cout << id << " is thinking " << duration << "ms\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    }

    void take_forks()
    {
        {
            std::lock_guard<std::mutex> lk{critical_region_mtx};  // enter critical region
            state = State::HUNGRY;  // record fact that philosopher i is State::HUNGRY
            {
                std::lock_guard<std::mutex> lk(output_mtx); // critical section for uninterrupted print
                std::cout << "\t\t" << "[" << id << "]"<< " is State::HUNGRY\n";
            }
            test(this);                        // try to acquire (a permit for) 2 forks
        }                                   // exit critical region
        both_forks.acquire();  // block if forks were not Acquired
    }

    void put_forks()
    { 
        std::lock_guard<std::mutex> lk{critical_region_mtx};    // enter critical region
        state = State::THINKING;  // philosopher has finished State::EATING
        test(left);               // see if left neighbor can now eat
        test(right);             // see if right neighbor can now eat
                                        // exit critical region by exiting the function
    }
    
    void eat()
    {
        size_t duration = my_rand(400, 800);
        {
            std::lock_guard<std::mutex> lk(output_mtx); // critical section for uninterrupted print
            std::cout << "\t\t\t\t" << std::to_string(id) << " left to eat: " << toEat << std::endl << " in " << duration << "ms\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
        toEat--;
    }

public:

    Philosopher(size_t _id, size_t _toEat) : 
        id(_id),
        toEat(_toEat)
    {};

    ~Philosopher() = default;

    void live() {
         while(toEat > 0) 
        {                         // repeat forever
            think();             // philosopher is State::THINKING
            take_forks();        // acquire two forks or block
            eat();               // yum-yum, spaghetti
            put_forks();         // put both forks back on table and check if neighbours can eat
        }
    }

    void setLeft(Philosopher* L) {
        left = L;
    }

    void setRight(Philosopher* R) {
        right = R;
    }
};

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cerr << "Need 2 arguments: 1. number of philospers 2. number of meals each one has to eat." << std::endl;
        exit(1);
    }

    size_t p = std::stol(argv[1]);
    if (p <= 2) {
        std::cerr << "Number of philosophers must be greater or equal to 3."<< std::endl;
        exit(1);
    }

    size_t m = std::stol(argv[2]);
    if (m < 1) {
        std::cerr << "Number of meals must be greater than 0."<< std::endl;
        exit(1);
    }
    
    // this error is meaningless
    std::vector<Philosopher*> philosophers;
    std::vector<std::jthread> jthreads;

    size_t i = 0;
    for(; i < p; i++) {
        philosophers.push_back(new Philosopher(i, m));
    }

    // set left and right pointer
    philosophers[0]->setLeft(philosophers[1]);
    philosophers[0]->setRight(philosophers[p-1]);

    for(i = 1; i < p-1; i++) {
        philosophers[i]->setLeft(philosophers[i+1]);
        philosophers[i]->setRight(philosophers[i-1]);
    }

    philosophers[i]->setLeft(philosophers[i]);
    philosophers[i]->setRight(philosophers[p-1]);
    
    for(i = 0; i < p; i++) {
        philosophers[i]->live();
        // std::jthread t([&] {philosophers[i]->live();});
        jthreads.push_back(std::jthread([&] {philosophers[i]->live();}));
        // jthreads.emplace_back([&] {philosophers[i]->live();});
    }

    // std::jthread t1([&] { philosophers[0]->live();}); // is captured by reference
    // std::jthread t2([&] { philosophers[1]->live();}); // is captured by reference
    // std::jthread t3([&] { philosophers[2]->live();}); // is captured by reference

    for(auto a : philosophers) {
        std::free(a);
    }

    // std::jthread t0([&] { philosopher(0); }); // [&] means every variable outside the ensuing lambda 
    // std::jthread t1([&] { philosopher(1); }); // is captured by reference
    // std::jthread t2([&] { philosopher(2); });
    // std::jthread t3([&] { philosopher(3); });
}
