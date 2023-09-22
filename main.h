#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define MAX_INPUT 1024

int process();
int shellstructure();
void commands(const char *input);
int path(const char *input, char *env[]);

#endif
