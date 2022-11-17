## a
```cpp
p = feld;
```
Funktioniert, da `feld` ein Array ist und somit ein Pointer auf das erste Element ist

## b
```cpp
feld = p;
```
Funktioniert nicht, da für das Array keine neue Zuweisung möglich ist

## c
```cpp
p = &feld[3];
```
Funktioniert, solange `feld` mindestens 4 Elemente hat

## d
```cpp
feld[2] = p[5];
```
Funktioniert, aber ergibt ggf. nur Sinn, wenn p nicht nur auf einen 'einfachen' Int-Wert zeigt, sondern danach noch weitere Elemente folgen 

## e
```cpp
p1 = p2 + i;
```
Funktioniert und greift auf das i-te Element nach p2 zu

## f
```cpp
p1 = i + p2;
```
Funktioniert, gleich wie e


## g
```cpp
i = p1 * p2;
```
Funktioniert nicht, da `*` nicht definiert ist für Pointer

## h
```cpp
i = p1 - p2;
```
Funktioniert, gibt die Anzahl der Elemente zwischen p1 und p2 zurück

## i
```cpp
i = p1 + p2;
```
Funktioniert nicht, da `+` nicht definiert ist für Pointer

---

Zweidimensionale Arrays sind im Speicher einfach nur "zeilenweise" hintereinander gespeichert. Weiß man nur, wie viele Elemente pro "Zeile" gespeichert sind, kennt man den Offset um innerhalb der "Zeilen" zu springen.
Hat man nur einen Pointer auf das erste Element, so kann man diesen Offset drauf addieren um auf die nächste "Zeile" zu kommen und darauf kann man dann nochmal den Index addieren um auf das entsprechende Element innerhalb der "Zeile" zu kommen.
```cpp
int zwei[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};

int* p = (int*) zwei;

printf("%d\n", *p);
printf("%d\n", *(p + 3));
printf("%d\n", *(p + 6 + 1));
```
Output:
```
1
4
8
```

---

Bei der Schreibweise `feld[i]` wird einfach `i` auf die Adresse `feld` addiert und man greift somit auf das i-te Element von `feld` zu.
Das die Addition auch umgekehrt funktioniert, kann man auch genau so auf `i` dann `feld` addieren und erhält ebenfalls das i-te Element von `feld`.
