#
# Einfuehrung in die Programmiersprache C++
#
# Makefile fuer Aufgabe 1 (easter)
#

CC              = gcc
INFILE          = years.in
OUTFILE         = easter_dates.out
CORRECT_OUTFILE = correct_easter_dates.out


easter: easter.o
	$(CC) easter.o -o easter

easter.o: easter.c
	$(CC) -Wall -c easter.c

test: easter
	./easter < $(INFILE) > $(OUTFILE)
	./run_test $(OUTFILE) $(CORRECT_OUTFILE)

