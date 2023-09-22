#include "main.h"

int path(const char *input, char *env[])
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
        return -1;
    }


    if (access(args[0], X_OK) == -1)
    {
 
        char *path = getenv("PATH");
        char *path_cp = strdup(path);
        char *path_tk = strtok(path_cp, ":");

        while (path_tk != NULL)
        {
            char command_path[MAX_INPUT];

            snprintf(command_path, sizeof(command_path), "%s/%s", path_tk, args[0]);

            if (access(command_path, X_OK) == 0)
            {
                
                if ((pid = fork()) == 0)
                {
                    execve(command_path, args, env);
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
                else if (pid < 0)
                {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    if (waitpid(pid, &status, 0) == -1)
                    {
                        perror("wait terminated");
                        exit(EXIT_FAILURE);
                    }
                    free(path_cp);
                    return 0;
                }
            }

            path_token = strtok(NULL, ":");
        }
       
        free(path_cp);
        return -1;
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

    return 0;
}

