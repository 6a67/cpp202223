#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;





void pow2(int& square_sum, int x) {
    // alternatively use lock_guard instead of lock and unlock
    // lock_guard<mutex> lock(square_sum_mutex);

    // create mutex for square_sum
    mutex square_sum_mutex;

    
    // lock the mutex
    square_sum_mutex.lock();
    square_sum += x * x;
    // unlock the mutex
    square_sum_mutex.unlock();

    // Race condition tritt hier nicht auf, indem der Zugriff auf square_sum gesperrt wird, wenn während gerade
    // ein anderer Thread auf die Variable zugreift
}

int main()
{
    int square_sum = 0;



    vector<thread> threads;
    for (int i = 1; i <= 20; i++)
    {
        // TODO
        // threads.push_back(thread(&pow2, square_sum, i));
        // does not work because the thread is called with a copy of the square_sum reference
        // in cpp references can not be copied because it does not have its own memory space and
        // therefore there is a compile error

        threads.push_back(thread(&pow2, ref(square_sum), i));
    }

    vector<thread>::iterator it;
    for (it = threads.begin(); it != threads.end(); it++)
    {
        (*it).join();
    }

    cout << "Sum of squares up to 20 is = " << square_sum << endl;
    return 0;
}
