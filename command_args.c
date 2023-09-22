#include "main.h"

/*
 * command_args - the function handles commalnn line arguments in the shell
 * @input: user input/shell command 
 * @pid: process id
 */


void command_args(const char *input)
{
    pid_t pid;
    int status;

    char *args[MAX_INPUT];
    int i = 0;

    char *token = strtok((char *)input, " ");
    while (token != NULL)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (i == 0)
    {
        // No command provided
        return;
    }

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("wait terminated");
            exit(EXIT_FAILURE);
        }
    }
}

