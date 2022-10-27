#include <stdio.h>

int main(int argc, char** argv) {
    char s[100];
    
    printf("Enter your first name: ");
    scanf("%99s", s);

    // TODO Check if the user entered only one word

    printf("Hello, %s!\n", s);
    return 0;
}