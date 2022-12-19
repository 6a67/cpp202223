#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <iterator>

struct random_string_generator
{
    std::string operator()()
    {
        int length = rand() % 5 + 5;
        std::string s;
        for (int i = 0; i < length; ++i)
            s += 'A' + rand() % 26 + (rand() % 2 ? 0 : 32);
        return s;
    }
};

int main()
{
    std::vector<std::string> v(100);
    generate(v.begin(), v.end(), random_string_generator());
    sort(v.begin(), v.end());
    copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}