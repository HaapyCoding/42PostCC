#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

void no(void)

{
  puts("Nope.");
                    /* WARNING: Subroutine does not return */
  exit(1);
}


void ok(void)

{
  puts("Good job.");
  return;
}



int main(void)

{
	size_t len_memset;
	int nbr_1;
	bool bool_1;
	char char_1;
	char char_2;
	char char_3;
	int zero;
	char scanf_str[24];
	char str_memset[9];
	unsigned int j;
	int i;
	int scanf_ret;
	int local_c;
	unsigned int unsigned_int;

	local_c = 0;
	printf("Please enter key: ");
	scanf_ret = scanf("%23s", scanf_str);
	if (scanf_ret != 1)
	{
		no();
	}
	if (scanf_str[1] != '0')
	{
		no();
	}
	if (scanf_str[0] != '0')
	{
		no();
	}
	fflush(stdin);
	memset(str_memset, 0, 9);
	str_memset[0] = 'd';
	zero = 0;
	j = 2;
	i = 1;
	while (true)
	{
		len_memset = strlen(str_memset);
		unsigned_int = j;
		bool_1 = false;
		if (len_memset < 8)
		{
			len_memset = strlen(scanf_str);
			bool_1 = unsigned_int < len_memset;
		}
		if (!bool_1)
			break;
		char_1 = scanf_str[j];
		char_2 = scanf_str[j + 1];
		char_3 = scanf_str[j + 2];
		nbr_1 = atoi(&char_1);
		str_memset[i] = (char)nbr_1;
		j = j + 3;
		i = i + 1;
	}
	str_memset[i] = '\0';
	nbr_1 = strcmp(str_memset, "delabere");
	if (nbr_1 == 0)
	{
		ok();
	}
	else
	{
		no();
	}
	return 0;
}