#include <stdio.h>
#include <string.h>

int main()
{
	int nbr;
	char str_start[4];
	char str_2[4];
	char str_3[4];
	char str_4[2];
	char scanf_input[100];
	char local_c;

	local_c = 0;
	str_start[0] = '_';
	str_start[1] = '_';
	str_start[2] = 's';
	str_start[3] = 't';
	str_2[0] = 'a';
	str_2[1] = 'c';
	str_2[2] = 'k';
	str_2[3] = '_';
	str_3[0] = 'c';
	str_3[1] = 'h';
	str_3[2] = 'e';
	str_3[3] = 'c';
	str_4[0] = 'k';
	str_4[1] = '\0';
	printf("Please enter key: ");
	printf("You need to put [%s]", str_start);
	scanf("%s", scanf_input);
	nbr = strcmp(scanf_input, str_start);
	if (nbr == 0)
	{
		printf("Good job.\n");
	}
	else
	{
		printf("Nope.\n");
	}
	return 0;
}