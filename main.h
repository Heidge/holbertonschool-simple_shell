#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
extern char **environ;

void cleaner(char *line);
void cleanup(char *line, char **args);
void handle_env(void);
void execute_command(char **args, char **av);
void execute_simple_command(char *line);
void handle_non_interactive(char **av);
char **split_line(char *line);
char *find_command_in_path(const char *cmd);
int main(int ac, char **av);
int handle_exit(char **args);
void handle_read_error(char *line, ssize_t read);

#endif /* MAIN_H */
