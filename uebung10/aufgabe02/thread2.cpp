#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

using namespace std;

void pow2(atomic<int>& square_sum, int x)
{
    // compiler will fallback to mutex based operations if the compiler does not support atomic operations
    square_sum += x * x;
}

/* Alternative:

atomic<int> square_sum(0);
void pow2(int x)
{
    square_sum += x * x;
} */

int main()
{
    atomic<int> square_sum(0);

    vector<thread> threads;
    for (int i = 1; i <= 20; i++)
    {
        threads.push_back(thread(&pow2, ref(square_sum), i));
        // Alternative:
        // threads.push_back(thread(&pow2, i));
    }

    vector<thread>::iterator it;
    for (it = threads.begin(); it != threads.end(); it++)
    {
        (*it).join();
    }

    cout << "Sum of squares up to 20 is = " << square_sum << endl;
    return 0;
}
