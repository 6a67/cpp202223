#include <stdio.h>
 
int main()
{
	int *ptr;
	ptr = new int();
	*ptr = 1111;
	ptr = new int();
	delete ptr;

	return 0;
}