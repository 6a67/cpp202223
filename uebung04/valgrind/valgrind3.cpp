#include <stdio.h>
#include <iostream>
 
int main()
{
	int *ptr;
	ptr = new int();
	*ptr = 1111;
	delete ptr;
	printf ("%i\n", *ptr);

	return 0;
}