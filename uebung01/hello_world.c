#include <stdio.h>

int main(int argc, char** argv) {
    char s[100];
    
    printf("Enter your first name: ");
    scanf("%99s", s);

    // is this even needed?
    // check if the user entered only one word
    if ((char) getchar() == ' ') {
        printf("ERROR: You entered more than one word.\n");
        return 1;
    }
    
    printf("Hello, %s!\n", s);
    return 0;
}