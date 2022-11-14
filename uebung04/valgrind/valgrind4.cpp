#include <stdio.h>
 
int main()
{
	int *ptr;
	ptr = new int();
	*ptr = 1111;
	printf ("%i\n", *(ptr+1));

	return 0;
}