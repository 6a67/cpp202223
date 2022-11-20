`cmake -DCMAKE_BUILD_TYPE=Debug ..`

b main - breakpoint at beginning of main
b N - breakpoint at line N
d N - delete breakpoint N
info break - list breakpoints

r - run until breakpoint
c - continue until next breakpoint
f - finish current function
s - run next line
s N - run next N lines
n - run next line (step over function calls)

p var - print value of var
bt - print backtrace

u - goes stack one level up
d - goes stack one level down
q - quit

r args - run with args
l - list 10 lines of source code

watch x == 0 - pause when x == 0
condition N x == 0 - set condition for breakpoint N

set var = 5 - set var to 5
set var = x - set var to x

call func() - call function func

display x - print x every time the program stops
undisplay x - remove display x