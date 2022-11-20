### definitely lost
Es ist keine Referenz auf einen allokierten Speicher mehr vorhanden (da diese Referenz z. B. "überschrieben" wurde oder die Variable out of scope gegangen ist)
Dadurch ist der Speicher nun aber auch nicht mehr freigebbar


### indirectly lost
Geht z. B. eine Referenz verloren, welche auf weiteren Referenzen zeigt (z. B. root in einem tree), so sind die weiteren Referenzen auch nicht mehr erreichbar und können nicht mehr freigegeben werden. Diese sind dann indirect lost, da dies dadurch behoben werden kann den definetly lost Fehler zu beheben


### possibly lost
Keine direkte Referenz mehr vorhanden, allerdings kann vielleicht z. B. durch Offsets immer noch auf den Speicher zugegriffen werden


### still reachable
Eine Referenz ist noch vorhanden, aber der Speicher wurde nicht freigegeben

### suppressed
Valgrind hat einige defaults von Fehlern, welche nicht angezeigt werden sollen. Diese werden dann als suppressed angezeigt


## valgrind1
`valgrind --leak-check=full ./valgrind1 9000` \
Schreibt über den eigentlichen zugewiesenen Speicher hinaus.
Man müsste überprüfen wie groß die eingegebene Zahl ist und dann nur passend Speicher reservieren bzw. keine größeren Zahlen erlauben

## valgrind2
`valgrind --leak-check=full ./valgrind2` \
Uninitialisierte Variable `foo` wird verwendet.
Man müsste `foo` initialisieren

## valgrind3
`valgrind --leak-check=full ./valgrind3` \
Der Pointer wird gefreed und danach weiterverwendet.
Man dürfte den Pointer nicht mehr verwenden, nachdem er gefreed wurde, bzw. kann man einen Check einbauen, ob der Pointer noch gültig ist.
(ggf. sollte man den Pointer auch direkt initialisieren)

## valgrind4
`valgrind --leak-check=full ./valgrind4` \
Es wird auf `*(ptr+1)` zugegriffen, was kein zugewiesener Speicher ist und der Pointer wird nicht gefreed.

## valgrind5
`valgrind --leak-check=full ./valgrind5` \
Hier gehen die Referenz des "ersten" Pointers verloren, wodurch man diese auch nicht mehr freen kann.
Man müsste diesen Speicher dann zuvor freen oder die Referenz woanders speichern.

## valgrind6
`valgrind --leak-check=full ./valgrind6` \
new/delete und malloc/delete werden hier gemischt

malloc called Constructor nicht, new schon \
free called Destructor nicht, delete schon



---
Potentiell fehlen überall Checks, ob `new` erfolgreich war und ob man überhaupt `delete` aufrufen kann