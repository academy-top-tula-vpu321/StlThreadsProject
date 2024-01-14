#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std::chrono_literals;

int global{};
std::mutex m;

void count()
{
    for (int i = 0; i < 5000; i++)
    {
        m.lock();
        global++;
        m.unlock();
    }
}


void func()
{
    for (int i = 0; i < 20; i++)
    {
        std::cout << "\tthread "
            << std::this_thread::get_id()
            << " " << i << "\n";
        std::this_thread::sleep_for(200ms);
    }
}

int main()
{
    /*
    std::thread th1(func);
    std::thread th2(func);

    for (int i = 0; i < 20; i++)
    {
        std::cout << "thread "
            << std::this_thread::get_id()
            << " " << i << "\n";
        std::this_thread::sleep_for(100ms);
    }

    th1.detach();
    th2.join();
    */

    std::thread t1(count);
    std::thread t2(count);

    t1.join();
    t2.join();

    std::cout << global << "\n";
}
