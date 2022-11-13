## Was sind die Vorteile von cmake?

- unabhängig von dem zugrundeliegenden build-System und Compiler
- sucht automatisch nach Programmen, Bibliotheken und Header-Dateien
- die Möglichkeit das Projekt in einem extra build file zu bauen der einafach und ohne Risiko zu löschen
- "Basic and common things are pretty easy and harder things are possible"

## Welche wichtigen Funktionen werden von cmake zur Verfügung gestellt?

- find_package(package)                     findet package ohne Angabe des Pfads (header files und Bibliotheken)
- set(VARNAME VALUE)                        setzt Flag die man sonst im Makefile setzen würde 
- add_subdirectory(subdirectory)            fügt ein Unterverzeichnis zum build hinzu
- add_executable(executable file.c)         fügt ein target für eine executable hinzu
- target_link_libraries(executable libary)  library wird mit executable verlinkt
- add_library(library libary.cpp)           eigene library erzeugen
- include_directories(dir)                  fügt die angegebenen Verzeichnisse zu denen hinzu, die der Compiler für die Suche nach Include-Dateien verwendet
- project(name)                             legt den Namen des Projekts fest und speichert ihn in der Variablen PROJECT_NAME

## Wie sind cmake-Projekte typischerweise aufgebaut?

- jede directory im projekt sollte ein CMakeLists.txt file enthalten
- 

## Unterschied zwischen In-Source- und Out-of-Source-Builds?

- Out-of-Source-Builds sind builds bei denen der build-tree seperat vom source tree in einer seperaten directory gespeichert ist, dies hat unter anderem den Vorteil, dass builds einfach und bedenkenlos gelöscht werden können, indem die build directory gelöscht wird (cmake -S ../ -B .)
- In-Source-Builds sind builds in der source directory und sind nicht zu empfehlen
