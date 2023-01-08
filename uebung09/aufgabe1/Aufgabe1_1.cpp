#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <iterator>

struct random_int_generator
{
    int operator()() { return std::rand() % 100 + 1; }
};

int main()
{
    std::vector<int> v(100);
    std::generate(v.begin(), v.end(), random_int_generator());
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
}