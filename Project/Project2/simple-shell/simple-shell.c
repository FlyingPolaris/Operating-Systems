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
	pid_t pid;
	int parent_wait = 1;
	int history_exist = 0;
	int num_of_args;
	int history_num_of_args;
	char *args[MAX_LINE / 2 + 1]; /* command line (of 80) has max of 40 arguments */
	char history_args[MAX_LINE / 2 + 1];
	int should_run = 1;
	int input_red = 0, output_red = 0;
	char input_file[MAX_LINE], output_file[MAX_LINE];
	char buffer[MAX_LINE];

	while (should_run)
	{
		printf("osh>");
		fflush(stdout);

		memset(buffer, 0, sizeof(buffer));
		input_red = output_red = 0;
		num_of_args = 0;
		fgets(buffer, MAX_LINE, stdin);
		char *token;
		char delim[] = " \n\t";
		for (token = strtok(buffer, delim); token != NULL; token = strtok(NULL, delim))
		{
			args[num_of_args] = token;
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
			parent_wait = 0;
			memset(args[num_of_args - 1], 0, sizeof(args[num_of_args - 1]));
			num_of_args--;
		}

		for (int i = 0; i < num_of_args; ++i)
		{
			if (strcmp(args[i], "<") == 0)
			{
				input_red = 1;
				strcpy(input_file, args[i + 1]);
			}
			if (strcmp(args[i], ">") == 0)
			{
				output_red = 1;
				strcpy(output_file, args[i + 1]);
			}
		}

		pid = fork();
		if (pid < 0)
		{
			printf("Fail to fork.\n");
			return -1;
		}
		else if (pid == 0)
		{
			
		}
		else
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