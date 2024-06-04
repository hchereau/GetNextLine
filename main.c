#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char *salut = "sa\nlut";
	printf("%ld\n", strchr(salut, '\n') - salut);
}
