#include <stdlib.h>
 
int main()
{
	int *ptr;
	ptr = new int();
	*ptr = 1111;
	free (ptr);
	return 0;
}
