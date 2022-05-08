typedef struct o {
	int		a;
	char	*b[6];
} o;
#include <stdio.h>
int main()
{
	o	temp = (o){
		0,
		(char *){
			"lol",
			"sku",
			0
		}
	};

	while (temp.b[temp.a])
		printf("%s\n", temp.b[temp.a++]);
}
