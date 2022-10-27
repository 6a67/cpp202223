#include <stdio.h>

int main(int argc, char** argv) {
    putchar('E');
    putchar('n');
    putchar('t');
    putchar('e');
    putchar('r');
    putchar(' ');
    putchar('w');
    putchar('o');
    putchar('r');
    putchar('d');
    putchar('s');
    putchar(':');
    putchar(' ');
    putchar('\n');
    
    int c;
    while((c = getchar()) != EOF) {
        if(c == ' ') {
            putchar('\n');
        } else {
            putchar(c);
        }
    }
}