#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <iterator>

struct random_int_generator
{
    int operator()() { return rand() % 100 + 1; }
};


int main()
{
    std::vector<int> v(100);
    generate(v.begin(), v.end(), random_int_generator());
    copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
}