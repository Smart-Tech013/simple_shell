#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * main - program that creates two separate processes and 
 * executes the 'ls' command in the child process
 * @argc: argument count 
 * @argv: argument vector
 */

int main(int argc, char *argv[])
{
	pid_t pid = fork();

	if (pid == 0)
	{
		execlp("ls", "ls", "-l", "-a", NULL);
	}
	else if (pid > 0)
	{
		printf("This is the parent process with PID of %d\n", pid);
	}
	else 
		perror("fork");
		return 1;

	return 0;
}

