#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char	*salut = "sal\nut";
	char	*test = strchr(salut, '\n');
	printf("%ld\n", test - salut);
}
