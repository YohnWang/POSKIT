#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trim.h"
#include"poscar.h"
#include"file.h"
POSCAR poscar;
POSCAR * p_poscar;

void cmdProcess(char *cmd, int argc, char argv[][100])
{
	int i;
	for (i = 0; i < strlen(cmd);i++)
		if(cmd[1] >= 'A' && cmd[1] <= 'Z')
			cmd[1] += 32;
	if (strcmp(cmd, "load") == 0 || strcmp(cmd, "l") == 0)
	{
		if (argc > 0)
			printf("%s\n", argv[0]);
		poscar = load_file();
		p_poscar = &poscar;
	}
	else if (strcmp(cmd, "print") == 0 || strcmp(cmd, "p") == 0)
	{
		print_file(poscar);
	}
	else if (strcmp(cmd, "save") == 0 || strcmp(cmd, "s") == 0)
	{
		save_file(poscar, strcmp(argv[0], "-f"));
	}
	else if (strcmp(cmd, "pte") == 0)
	{
		print_PTE();
	}
	//else if (strcmp(cmd, "x^2+(y-pow(x^2,1.0/3))^2=1") == 0)
		//;
	else if (strcmp(cmd, "hahaha") == 0|| strcmp(cmd, "h") == 0)
		printf("\n    PUHAHAHAHA!   ( ^_^ ) \n\n");
	else if (strcmp(cmd, "fix") == 0 || strcmp(cmd, "f") == 0)
	{
		int n;
		if (poscar.suc == 0)
		{
			printf("\n");
			printf("    Please load the file first.[load/l]\n");
			printf("\n");
			return;
		}
		if (argc > 0)
		{
			if (!(p_poscar->is_selective))
			{
				fix_file(p_poscar);
			}
			if (strcmp(argv[0], "-h") == 0)
				n = fix_by_height(p_poscar, atof(argv[1]), atof(argv[2]));
			//else if (strcmp(argv[0], "-a") == 0)
				//n = fix_file(p_poscar);
			else if (strcmp(argv[0], "-e") == 0)
				n = fix_by_elem(p_poscar, argc, argv);
			else if (strcmp(argv[0], "-l") == 0)
				n = fix_by_lines(p_poscar, atoi(argv[1]), atoi(argv[2]));
			else
			{
				n = 0;
				printf("\n    Invalid Parameter!!!\n");
				printf("    What are you doing?\n");
				printf("\n");
				return;
			}
		}
		else
		{
			n = fix_file(p_poscar);
		}
		FixInfoOutput(n);
	}
}

void main_loop()
{
	char str[100];
	char str1[100];
	char cmd[10];
	char margv[10][100];
	char *ch;
	int len,i,num,flag,bi;
	load_PTE_file();
	while (1)
	{
		bi = flag = i = 0;
		num = -1;
		printf(">> ");
		scanf("%[^\n]%*c", str);
		ch = LTrim(str);
		len = strlen(ch);
		while (*ch != ' ' && *ch != '\0' && *ch != '-')
		{
			if (i == 9)break;
			cmd[i++] = *ch;
			ch++;
		}
		cmd[i] = '\0';
		if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "e") == 0)
		{
			printf("-----------------------------\n");
			printf("    Thank you for using!!!   \n");
			printf("-----------------------------\n");
			break;
		}
		while (*ch != '\0')
		{
			
			if (flag)//非空格
			{
				if (*ch == ' ')
				{
					flag = 0;
					margv[num][bi] = '\0';
					bi = 0;
				}
				else
				{
					margv[num][bi++] = *ch;
				}
			}
			else
			{
				if (*ch != ' ')
				{
					num++;
					margv[num][bi++] = *ch;
					flag = 1;
				}
			}
			if (flag == 1)//结尾处理
			{
				if (*(ch + 1) == '\0')
				{
					margv[num][bi] = '\0';
				}
			}
			ch++;
		}
		num++;
		cmdProcess(cmd,num,margv);
	}
}

//for (i = 0; i < num; i++)
//{
//	bi = 0;
//	while (margv[i][bi] != '\0')
//	{
//		printf("%c", margv[i][bi++]);
//	}
//	printf("\n");
//}