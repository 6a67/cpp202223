# 1
Nehmen Sie an, sie haben eine Software programmiert, mit deren Hilfe sich ähnlich wie in unserer Software
2D Sprites rendern lassen. Anders als bei unserem Ansatz haben Sie sich allerdings dazu entschieden, keine
eigene Template-Klasse zur Repräsentation von 2D-Koordinaten (analog zu unserer Klasse Vector) zu
schreiben. Stattdessen sollen die Renderable-Klassen direkt über den Typ des Vektors vertemplatet werden,
d.h., der Typ zur Vektor-Repräsentation ist ein Template-Parameter der Klasse Renderable und ihrer
Unterklassen. Erläutern Sie vor- und Nachteile dieses Ansatzes.
- Vorteile
  - Flexibler: Renderable-Klassen können mit allen Vektoren verwendet werden, die die benötigten Methoden implementieren.
  - Renderable-Klasse ist unabhängig von der Implementierung des Vektors
- Nachteile
  - Gibt Auswahl des Vector-Typs an den Nutzer weiter
    - Unübersichtlich: Man muss wissen, welche Eigenschaften der Vector haben muss
  - Erhöht Compiletime
    - Viele extra Klassen müssen kompiliert werden
    - Ggf. aber Optimierungen durch Compiler möglich -> könnte aber Runtime positiv beeinflussen


## 2
Neben der Geometrie sollen die in 1.) genutzten Typen auch Felder mit Farbinformationen enthalten.
Skizzieren Sie wie sich mit Hilfe von Traits feststellen lässt, ob der Typ, mit dem ein wie in 1)
vertemplatetes Renderable instanziert wird, Komponenten zum Speichern der r, g und b Werte einer Farbe
unterstützt. Vervollständigen Sie das in der Datei Traits.cpp gegebene Programmgerüst sinnvoll.
