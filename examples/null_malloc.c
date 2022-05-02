#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	char	*a;

	a = malloc(0);
	printf("%p, %lld\n", a, a);
}
