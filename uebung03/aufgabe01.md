# Vorteile
- Ist nicht an ein Build-System, wie z.B. make, gebunden
- Automatisiert die Suche nach Libraries
- Für größere Projekte besser geeignet

# Aufbau und Funktionen
- CMakeLists.txt
  - Jeder Ordner hat eine CMakeLists.txt und erbt die Einstellungen des übergeordneten Ordners
  - Projektnamen mit `project(NAME)` setzen
  - Variablen mit `set(VARIABLE VALUE)` setzen
  - Subdirectories mit `add_subdirectory(SUBDIRECTORY)` hinzufügen
  - Mit `include_directories(DIRECTORY)` wird festgelegt, in welchen Ordnern nach Source-Dateien gesucht werden soll
  - Mit `add_executable(NAME SOURCE)` wird angegeben, welche Executable erstellt werden soll
  - Mit `target_link_libraries(NAME LIBRARY)` wird angegeben, welche Libraries für das Program NAME verwendet werden sollen
  - Mit `find_package(PACKAGE)` wird nach einer Library gesucht
  - Erlaubt auch foreach Loops
  - Mit `add_library(NAME SOURCE)` wird eine Library erstellt

# In-Source- und Out-of-Source
- Out-of-Source
  - Erstellt einen Ordner, in dem alle Build-Dateien erstellt werden
  - `mkdir build && cd build && cmake ..`
- In-Source
  - Erstellt alle Build-Dateien im aktuellen Ordner