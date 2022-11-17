## valgrind1
`valgrind --leak-check=full ./valgrind1 9000`
Schreibt über den eigentlichen zugewiesenen Speicher hinaus.
Man müsste überprüfen wie groß die eingegebene Zahl ist und dann nur so viel Speicher reservieren bzw. keine größeren Zahlen erlauben

## valgrind2
`valgrind --leak-check=full ./valgrind2`
Uninitialisierte Variable `foo` wird verwendet.
Man müsste `foo` initialisieren

## valgrind3
`valgrind --leak-check=full ./valgrind3`
Der Pointer wird gefreed und danach weiterverwendet. Außerdem geht die Referenz auf den zuerst erstellten Pointer verloren (wodurch man diese auch nicht mehr freen kann) und die Referenz wird manuell auf eine Adresse gesetzt, was man nicht tun sollte.
Man dürfte den Pointer nicht mehr verwenden, nachdem er gefreed wurde, bzw. man kann einen Check einbauen, ob der Pointer noch gültig ist und man sollte den zuerst erstellten Pointer freen oder zwischen speichern, bevor dieser überschrieben wird
(ggf. sollte man den Pointer auch direkt initialisieren)

## valgrind4
`valgrind --leak-check=full ./valgrind4`
Gleiches Problem wie zuvor mit dem Pointer setzen und es wird auf `*(ptr+1)` zugegriffen, was kein valider Speicher ist.

## valgrind5
`valgrind --leak-check=full ./valgrind5`
Gleiches Problem mit den Pointern wie bei valgrind3. Hier gehen die Referenzen des "ersten" und "zweiten" Pointers verloren, wodurch man diese auch nicht mehr freen kann

## valgrind6
`valgrind --leak-check=full ./valgrind6`
Gleiches Problem wie zuvor, allerdings wird nun der `ptr` der auf die Adresse `1111` zeigt gefreed, allerdings wurde an dieser Stelle nicht Speicher allokiert, weshalb hier Dinge gefreed werden, die gar nicht frei gemacht werden sollen