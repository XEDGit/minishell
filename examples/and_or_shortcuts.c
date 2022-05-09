#include <unistd.h>

int main()
{
	char *s = "hello";
	if (0 && *s++)
	;
	write(1, s, 5);
}
