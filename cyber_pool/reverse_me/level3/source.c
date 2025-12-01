
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 main(void)

{
	ulong uVar1;
	int iVar2;
	size_t sVar3;
	bool bVar4;
	char local_4c;
	char local_4b;
	char local_4a;
	undefined1 local_49;
	char str[31];
	char local_29[9];
	unsigned long j;
	int local_18;
	int local_14;
	int scanf_ret;
	int local_c;

	local_c = 0;
	printf("Please enter key: ");
	scanf_ret = __isoc99_scanf("%23s");
	if (scanf_ret != 1)
	{
		___syscall_malloc();
	}
	if (str[1] != '2')
	{
		___syscall_malloc();
	}
	if (str[0] != '4')
	{
		___syscall_malloc();
	}
	fflush(stdin);
	memset(local_29, 0, 9);
	local_29[0] = '*';
	local_49 = 0;
	j = 2;
	local_14 = 1;
	while (true)
	{
		sVar3 = strlen(local_29);
		uVar1 = j;
		bVar4 = false;
		if (sVar3 < 8)
		{
			sVar3 = strlen(str);
			bVar4 = uVar1 < sVar3;
		}
		if (!bVar4)
			break;
		local_4c = str[j];
		local_4b = str[j + 1];
		local_4a = str[j + 2];
		iVar2 = atoi(&local_4c);
		local_29[local_14] = (char)iVar2;
		j = j + 3;
		local_14 = local_14 + 1;
	}
	local_29[local_14] = '\0';
	local_18 = strcmp(local_29, "********");
	if (local_18 == -2)
	{
		___syscall_malloc();
	}
	else if (local_18 == -1)
	{
		___syscall_malloc();
	}
	else if (local_18 == 0)
	{
		____syscall_malloc();
	}
	else if (local_18 == 1)
	{
		___syscall_malloc();
	}
	else if (local_18 == 2)
	{
		___syscall_malloc();
	}
	else if (local_18 == 3)
	{
		___syscall_malloc();
	}
	else if (local_18 == 4)
	{
		___syscall_malloc();
	}
	else if (local_18 == 5)
	{
		___syscall_malloc();
	}
	else if (local_18 == 0x73)
	{
		___syscall_malloc();
	}
	else
	{
		___syscall_malloc();
	}
	return 0;
}
