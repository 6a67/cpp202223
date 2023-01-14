#include <iostream>
#include <future>
#include <chrono>
#include <vector>

using namespace std;

vector<future<int>> v(20);
int square_sum = 0;

int square(int x) {
    return x * x;
}

int main() {
    for(int i = 1; i <= 20; i++) {
        v[i - 1] = async(std::launch::async, &square, i);
    }

    for(auto &f : v) {
        square_sum += f.get();
    }

    cout << "Sum of squares up to 20 is = " << square_sum << endl;
    return 0;
}
