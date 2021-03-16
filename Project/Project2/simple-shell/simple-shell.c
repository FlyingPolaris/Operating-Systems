/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 80 /* 80 chars per line, per command */

void get_into_history(char **, char **, int, int);

int main(void)
{
	int history_exist = 0;
	int num_of_args;
	int history_num_of_args;
	char *args[MAX_LINE / 2 + 1]; /* command line (of 80) has max of 40 arguments */
	char history_args[MAX_LINE / 2 + 1];
	int should_run = 1;
	char buffer[MAX_LINE];

	while (should_run)
	{
		printf("osh>");
		fflush(stdout);

		memset(buffer, 0, sizeof(buffer));

		num_of_args = 0;
		fgets(buffer, MAX_LINE, stdin);
		char *token;
		char delim[] = " \n\t";
		for (token = strtok(buffer, delim); token != NULL; token = strtok(NULL, delim))
		{
			memset(args, 0, sizeof(token));
			strcpy(args[num_of_args], token);
			num_of_args++;
		}

		if (strcmp(arg[0], "exit") == 0)
		{
			should_run = 0;
			continue;
		}

		if (strcmp(arg[0], "!!") == 0)
		{
			get_into_history(args, history_args, history_num_of_args, history_exist);
			if (strcmp(arg[0], "!!" == 0))
				continue;
		}
		else
		{
			history_exist = 1;
			history_num_of_args = num_of_args;
			for (int i = 0; i < num_of_args; ++i)
			{
				memset(history_args[i], 0, sizeof(args[i]));
				strcpy(history_args[i], args[i]);
			}
		}

		
		if (strcmp(args[num_of_args - 1], "&") == 0)
		{
		}

		/**
         	 * After reading user input, the steps are:
         	 * (1) fork a child process
         	 * (2) the child process will invoke execvp()
         	 * (3) if command included &, parent will invoke wait()
         	 */
	}

	return 0;
}

void get_into_history(char **args, char **history_args, int history_num_of_args, int history_exist)
{
	if (!history_exist)
	{
		printf("No commands in history.\n");
	}
	else
	{
		for (int i = 0; i < history_num_of_args; ++i)
		{
			memset(args[i], 0, sizeof(history_args[i]));
			strcpy(args[i], history_args[i]);
			printf("%s ", args[i]);
		}
	}
}