#include "main.h"


int shellstructure()
{

	char userInput[MAX_INPUT];

	while(1)
	{
		printf("myshell> ");

		if (fgets(userInput, sizeof(userInput), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		userInput[strcspn(userInput, "\n")] = '\0';

		commands(userInput);

		//exiting the shell
		if (strcmp (userInput, "exit") == 0)
		{
			exit(EXIT_FAILURE);
		}
	}

	return (0);
}

void commands(const char *input)
{
	pid_t pid;

	int status;

	if (strcmp(input, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}


	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		char *argv[] = {(char *)input, NULL};
		char *envp[] = {NULL};

		execve(input, argv, envp);

		perror("command not found");
		exit(EXIT_FAILURE);
	}
	else 
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("wait terminated");
			exit(1);
		}
	}

}
