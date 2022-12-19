#include <algorithm> 
#include <functional>
#include <iostream>
#include <vector>


struct adder: public std::unary_function<int, void> {
    adder(): sum(0) {}
    void operator()(int i) { sum += i; }
    int sum;
};

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    adder a = std::for_each(v.begin(), v.end(), adder());
    std::cout << a.sum << std::endl;
}