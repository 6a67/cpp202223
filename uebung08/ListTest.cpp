#include <iostream>
#include "List.hpp"

void printInt(int x) { std::cout << x << std::endl; }

int main()
{
    asteroids::List<int> l;
    for (int i = 0; i < 10; i++)
    {
        l.insert(i);
    }
    l.for_each(printInt);
    return 0;
}