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


// void reverse()
// {
// 	char *str = "delabere";
// 	int j = 0;
// 	int i = 0;
// 	int k;
// 	size_t len_memset;
	
// 	i = 1;
// 	j = 2;

// 	while (true)
// 	{
// 		len_memset = strlen(str_memset);
// 		k = j;
// 		bool_1 = false;
// 		if (len_memset < 8)
// 		{
// 			len_memset = strlen(scanf_str);
// 			bool_1 = check_j < len_memset;
// 		}
// 		if (!bool_1)
// 			break;
// 		char_1 = scanf_str[j];
// 		char_2 = scanf_str[j + 1];
// 		char_3 = scanf_str[j + 2];
// 		nbr_1 = atoi(&char_1);
// 		str_memset[i] = (char)nbr_1;
// 		j = j + 3;
// 		i = i + 1;
// 	}

// }


int main(void)

{
	size_t len_memset;
	int nbr_1;
	bool bool_1;
	char char_1;
	char scanf_str[24];
	char str_memset[9];
	unsigned int j;
	int i;
	int scanf_ret;

	unsigned int check_j;

	printf("Please enter key: ");
	scanf_ret = scanf("%23s", scanf_str);
	printf("[%d]\n", scanf_ret);
	printf("scanf gives : [%s]\n", scanf_str);
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
	j = 2;
	i = 1;
	while (true)
	{
		printf("start while str_memset is : [%s]\n", str_memset);
		len_memset = strlen(str_memset);
		printf("start while len_memset is : [%zu]\n", len_memset);
		check_j = j;
		bool_1 = false;
		if (len_memset < 8)
		{
			len_memset = strlen(scanf_str);
			bool_1 = check_j < len_memset;
		}
		if (!bool_1)
			break;
		char_1 = scanf_str[j];
		nbr_1 = atoi(&char_1);
		printf("nbr_1 is [%d]\n", nbr_1);
		str_memset[i] = (char)nbr_1;
		printf("and so str_memset[%d] is : [%c]\n", i, str_memset[i]);
		j = j + 3;
		i = i + 1;
		printf("end while str_memset is [%s]\n", str_memset);
	}
	str_memset[i] = '\0';
	nbr_1 = strcmp(str_memset, "delabere");
	if (nbr_1 == 0)
	{
		ok();
	}
	else
	{
		printf("[%s]\n", str_memset);
		no();
	}
	return 0;
}