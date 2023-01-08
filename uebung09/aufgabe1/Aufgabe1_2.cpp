#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>

struct random_string_generator
{
    std::string operator()()
    {
        int length = std::rand() % 6 + 5;
        std::string s;
        for (int i = 0; i < length; ++i)
        {
            // s += 'A' + std::rand() % 26 + (std::rand() % 2 ? 0 : 32);

            // generate random char with std library
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> char_distribution('A', 'Z');
            s += char_distribution(gen) + (std::rand() % 2 ? 0 : 32);
        }
        return s;
    }
};

int main()
{
    std::vector<std::string> v(100);
    std::generate(v.begin(), v.end(), random_string_generator());
    std::sort(v.begin(), v.end());
    std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}