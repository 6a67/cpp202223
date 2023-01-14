# 1
```cpp
vector<int> v = {1, 4, 2, 8, 5, 7};

copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
cout << endl;

auto it = remove_if(v.begin(), v.end(),
                    bind(bind(equal_to<int>(), _1, 0),
                         bind(modulus<int>(), _1, 2)));

copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
cout << endl;

return 0;
```

```cpp
vector<int> v = {1, 4, 2, 8, 5, 7};

copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
cout << endl;

auto eqt = bind(equal_to<int>(), _1, 0); // eqt(x) = equal_to<int>()(x, 0) // check if x is 0
auto mod = bind(modulus<int>(), _1, 2); // mod(x) = modulus<int>()(x, 2) // check mod 2 of x
// bind(eqt, mod) = eqt(mod(x)) = eqt(modulus<int>()(x, 2)) = equal_to<int>()(modulus<int>()(x, 2), 0) // check if mod 2 of x is 0 -> check if x is even

auto it = remove_if(v.begin(), v.end(),
                    bind(eqt, mod));

copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
cout << endl;

return 0;
```

Das Programm soll also alle geraden Zahlen aus dem Vector entfernen.

# 2
```cpp
auto eqt = bind(equal_to<int>(), _1, 0) // eqt(x) = equal_to<int>()(x, 0) // check if x is 0
auto mod = bind(modulus<int>(), _1, 2)) // mod(x) = modulus<int>()(x, 2) // check mod 2 of x
auto even = bind(eqt, mod) // = eqt(mod(x)) = eqt(modulus<int>()(x, 2)) = equal_to<int>()(modulus<int>()(x, 2), 0) // check if mod 2 of x is 0 -> check if x is even
```
Signatur von bind ist: `bind(f, _1, _2, ..., _n) = f(_1, _2, ..., _n)`, aber es geht auch `bind(f, _2, _1) = f(_1, _2)` um z. B. die Reihenfolge der Argumente zu ändern. \
`bind(bind(equal_to<int>(),_1, 0), bind(modulus<int>(), _1, 2))`: \
`bind(equal_to<int>(), _1, 0)` bindet das erste Argument, was an `equal_to<int>()` übergeben wird, mit `_1` und das zweite Argument mit der Konstante 0. `_1` ist hier dann der Return-Wert von `bind(modulus<int>(), _1, 2)`, da alle Arguments, welche nach der Funktion stehen, als Argumente an die Funktion übergeben werden. \
`bind(modulus<int>(), _1, 2)` bindet das erste Argument, was an `modulus<int>()` übergeben wird, mit `_1` und das zweite Argument mit der Konstante 2. `_1` ist hier dann erste Argument, welches an die äußere bind-Funktion übergeben wird.


# 3
Der return iterator `it` zeigt auf das neue Ende der Range. Ein Fix wäre, die Elemente danach mit `v.erase(it, v.end())` zu löschen, oder nur die Elemente bis `it` mit `copy(v.begin(), it, ostream_iterator<int>(cout, " "));` zu printen

