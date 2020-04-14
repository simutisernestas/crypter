#ifndef LETSCODE_TIMER_H
#define LETSCODE_TIMER_H

#include <iostream>
#include <chrono>
#include <thread>
#include <string>

using namespace std::chrono;
using std::string;

namespace LC
{
    class Timer
    {
    private:
        high_resolution_clock::time_point t1, t2;
        string _id;
    public:
        Timer()
        {
            t1 = high_resolution_clock::now();
        }

        Timer(string id)
        {
            t1 = high_resolution_clock::now();
            _id = id;
        }

        ~Timer()
        {
            t2 = high_resolution_clock::now();
            std::cout << (_id.empty() ? "" : _id + ' ') << "took "
                      << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
                      << " milliseconds :)\n";
        }
    };
}

#endif //LETSCODE_TIMER_H
