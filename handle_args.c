/*task2*/
#include <stdio.h>

/**
 * main: checks the code
 * Description: using the main function
 *
 * Return: Always 0
 */
int main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t nread;
	char *token;
	char *argv[10];
	int g, status;
	pid_t pid;

	while (1)
	{
		puts("latenightfun");
		nread = getline(&buffer, &bufsize, stdin);

		if (nread == -1)
		{
			puts("\n");
			exit(EXIT_SUCCESS);
		}
		if (buffer[nread - 1] == '\n')
			buffer[nread - 1] = '\0';

		token = strtok(buffer, " ");

		g = 0;

		while (token != NULL)

		{

			argv[g++] = token;

			token = strtok(NULL, " ");

		}
		argv[g] = NULL;
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
		}
		else if (pid == 0)
		{
			execve(argv[0], argv, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
	free(buffer);
	return (EXIT_SUCCESS);
}
