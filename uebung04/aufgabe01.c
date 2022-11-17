#include <stdio.h>

/*

## a
```cpp
p = feld;
```

## b
```cpp
feld = p;
```

## c
```cpp
p = &feld[3];
```

## d
```cpp
feld[2] = p[5];
```

## e
```cpp
p1 = p2 + i;
```

## f
```cpp
p1 = i + p2;
```

## g
```cpp
i = p1 * p2;
```

## h
```cpp
i = p1 - p2;
```

## i
```cpp
i = p1 + p2;
```
*/


int main() {
    int zwei[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};

    int* p = (int*) zwei;

    printf("%d\n", *p);
    printf("%d\n", *(p + 3));
    printf("%d", *(p + 6 + 1));

    return 0;

}