#include<iostream>
#include<vector>
#include<iterator>
#include<functional>
#include<typeinfo>

using namespace std;
using namespace std::placeholders;


int main() {
    vector<int> v = {1, 4, 2, 8, 5, 7};

    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    auto it = remove_if(v.begin(), v.end(),
                        bind(bind(equal_to<int>(), _1, 0),
                            bind(modulus<int>(), _1, 2)));

    v.erase(it, v.end());

    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}