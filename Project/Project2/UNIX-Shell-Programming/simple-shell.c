/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_LINE 80 /* 80 chars per line, per command */

int main(void)
{
	pid_t pid;
	pid_t pipe_pid;
	int parent_wait;
	int history_exist = 0;
	int num_of_args;
	int history_num_of_args;
	char *args[MAX_LINE / 2 + 1]; /* command line (of 80) has max of 40 arguments */
	char history_args[MAX_LINE / 2 + 1][MAX_LINE / 2 + 1];
	char *pipe_args[MAX_LINE / 2 + 1];
	int should_run = 1;
	int input_red, output_red;
	int pipe_created;
	int num_of_pipe_args;
	int filedes[2];
	char input_file[MAX_LINE], output_file[MAX_LINE];
	char buffer[MAX_LINE];

	while (should_run)
	{
		printf("osh>");
		fflush(stdout);

		memset(buffer, 0, sizeof(buffer));
		input_red = output_red = 0;
		pipe_created = 0;
		num_of_args = 0;
		num_of_pipe_args = 0;
		parent_wait = 1;
		filedes[0] = filedes[1] = 0;
		fgets(buffer, MAX_LINE, stdin);
		char *token;
		char delim[] = " \n\t";
		for (token = strtok(buffer, delim); token != NULL; token = strtok(NULL, delim))
		{
			args[num_of_args] = token;
			num_of_args++;
		}
		args[num_of_args] = NULL;

		if (strcmp(args[0], "exit") == 0)
		{
			should_run = 0;
			continue;
		}

		if (strcmp(args[0], "!!") == 0)
		{
			if (!history_exist)
			{
				printf("No commands in history.\n");
			}
			else
			{
				for (int i = 0; i < history_num_of_args; ++i)
				{
					args[i] = history_args[i];
					printf("%s ", args[i]);
				}
				num_of_args = history_num_of_args;
				printf("\n");
			}
			if (strcmp(args[0], "!!") == 0)
				continue;
		}
		else
		{
			history_exist = 1;
			history_num_of_args = num_of_args;
			for (int i = 0; i < num_of_args; ++i)
			{
				strcpy(history_args[i], args[i]);
			}
		}

		if (strcmp(args[num_of_args - 1], "&") == 0)
		{
			parent_wait = 0;
			num_of_args--;
			args[num_of_args] = NULL;
		}

		for (int i = 0; i < num_of_args; ++i)
		{
			if (args[i] && strcmp(args[i], "<") == 0)
			{
				input_red = 1;
				strcpy(input_file, args[i + 1]);
				args[i] = args[i + 1] = NULL;
				num_of_args -= 2;
			}
			if (args[i] && strcmp(args[i], ">") == 0)
			{
				output_red = 1;
				strcpy(output_file, args[i + 1]);
				args[i] = args[i + 1] = NULL;
				num_of_args -= 2;
			}
			if (args[i] && strcmp(args[i], "|") == 0)
			{
				pipe_created = 1;
				args[i] = NULL;
				for (int j = i + 1; j < num_of_args; ++j)
				{
					pipe_args[num_of_pipe_args] = args[j];
					args[j] = NULL;
					num_of_pipe_args++;
				}
				pipe_args[num_of_pipe_args] = NULL;
				num_of_args -= num_of_pipe_args;
			}
		}

		pid = fork();
		if (pid < 0)
		{
			fprintf(stderr, "Fail to fork.\n");
			return -1;
		}
		else if (pid == 0)
		{
			if (input_red)
			{
				int fd;
				fd = open(input_file, O_RDONLY);
				dup2(fd, STDIN_FILENO);
			}
			if (output_red)
			{
				int fd;
				fd = open(output_file, O_CREAT | O_RDWR, S_IRWXU);
				dup2(fd, STDOUT_FILENO);
			}
			if (pipe_created)
			{
				if (pipe(filedes) == -1)
				{
					fprintf(stderr, "Creating pipe failed.\n");
					return 1;
				}
				else
				{
					pipe_pid = fork();
					if (pipe_pid < 0)
					{
						fprintf(stderr, "Fork failed when creating pipe.\n");
						return 1;
					}
					else if (pipe_pid == 0)
					{
						close(filedes[0]);
						dup2(filedes[1], STDOUT_FILENO);
						execvp(args[0], args);
						close(filedes[1]);
						exit(0);
					}
					else
					{
						close(filedes[1]);
						dup2(filedes[0], STDIN_FILENO);
						execvp(pipe_args[0], pipe_args);
						close(filedes[0]);
						wait(NULL);
					}
				}
			}
			else
			{
				execvp(args[0], args);
				wait(NULL);
			}
		}
		else
		{
			if (parent_wait)
				wait(NULL);
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
