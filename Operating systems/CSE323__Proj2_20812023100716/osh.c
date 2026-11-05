/*
 * osh.c - a simple UNIX shell
 *
 * Features:
 *   - runs each command in a child process (fork + execvp), parent waits
 *   - "&" at the end of a command runs it in the background
 *   - "!!" repeats the most recent command (history feature)
 *   - input redirection  ( < file ) and output redirection ( > file ) using dup2()
 *   - one pipe between two commands ( cmd1 | cmd2 ) using pipe() and dup2()
 *   - built-ins: exit, cd
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* The maximum length command */

/* Split "line" into words. Fills args[] (NULL terminated), returns word count. */
static int parse(char *line, char **args)
{
	int n = 0;
	char *tok = strtok(line, " \t\r\n");

	while (tok != NULL && n < MAX_LINE / 2) {
		args[n++] = tok;
		tok = strtok(NULL, " \t\r\n");
	}
	args[n] = NULL;
	return n;
}

/* Index of the word equal to s in args[], or -1 if it is not there. */
static int find_token(char **args, const char *s)
{
	for (int i = 0; args[i] != NULL; i++)
		if (strcmp(args[i], s) == 0)
			return i;
	return -1;
}

/*
 * Runs in the CHILD process: set up < and > redirection with dup2(),
 * then replace the process image with the command using execvp().
 */
static void exec_command(char **args) __attribute__((noreturn));
static void exec_command(char **args)
{
	int in = find_token(args, "<");
	int out = find_token(args, ">");
	int fd;

	if (in >= 0) {
		if (args[in + 1] == NULL) {
			fprintf(stderr, "osh: missing input file after '<'\n");
			_exit(1);
		}
		fd = open(args[in + 1], O_RDONLY);
		if (fd < 0) {
			perror(args[in + 1]);
			_exit(1);
		}
		dup2(fd, STDIN_FILENO);   /* stdin now reads from the file */
		close(fd);
		args[in] = NULL;          /* cut the command off before '<' */
	}

	if (out >= 0) {
		if (args[out + 1] == NULL) {
			fprintf(stderr, "osh: missing output file after '>'\n");
			_exit(1);
		}
		fd = open(args[out + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0) {
			perror(args[out + 1]);
			_exit(1);
		}
		dup2(fd, STDOUT_FILENO);  /* stdout now writes to the file */
		close(fd);
		args[out] = NULL;         /* cut the command off before '>' */
	}

	if (args[0] == NULL) {
		fprintf(stderr, "osh: missing command\n");
		_exit(1);
	}

	execvp(args[0], args);
	perror(args[0]);              /* only reached if execvp failed */
	_exit(127);
}

/* Run a single command (no pipe). */
static void run_simple(char **args, int background)
{
	pid_t pid = fork();

	if (pid < 0) {
		perror("fork");
		return;
	}
	if (pid == 0)
		exec_command(args);

	if (background)
		printf("[background] pid %d\n", pid);
	else
		waitpid(pid, NULL, 0);
}

/* Run "left | right": two children connected by a pipe. */
static void run_pipe(char **left, char **right, int background)
{
	int fd[2];
	pid_t p1, p2;

	if (pipe(fd) < 0) {
		perror("pipe");
		return;
	}

	p1 = fork();
	if (p1 < 0) {
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		return;
	}
	if (p1 == 0) {                    /* child 1: writer */
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);   /* stdout -> pipe write end */
		close(fd[1]);
		exec_command(left);
	}

	p2 = fork();
	if (p2 < 0) {
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		waitpid(p1, NULL, 0);
		return;
	}
	if (p2 == 0) {                    /* child 2: reader */
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);    /* stdin <- pipe read end */
		close(fd[0]);
		exec_command(right);
	}

	/* The parent must close both ends, otherwise the reader never sees EOF. */
	close(fd[0]);
	close(fd[1]);

	if (background) {
		printf("[background] pids %d %d\n", p1, p2);
	} else {
		waitpid(p1, NULL, 0);
		waitpid(p2, NULL, 0);
	}
}

int main(void)
{
	char *args[MAX_LINE / 2 + 1];   /* command line arguments */
	char line[MAX_LINE + 2];        /* input line (+ newline + NUL) */
	char history[MAX_LINE + 2] = ""; /* most recent command */
	int should_run = 1;             /* flag to determine when to exit program */

	while (should_run) {
		/* collect finished background children so they don't stay zombies */
		while (waitpid(-1, NULL, WNOHANG) > 0)
			;

		printf("osh>");
		fflush(stdout);

		if (fgets(line, sizeof(line), stdin) == NULL) {  /* Ctrl-D */
			printf("\n");
			break;
		}

		size_t len = strlen(line);
		if (len > 0 && line[len - 1] != '\n' && !feof(stdin)) {
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;                /* discard the rest of the long line */
			fprintf(stderr, "osh: command too long (max %d characters)\n",
				MAX_LINE);
			continue;
		}
		line[strcspn(line, "\n")] = '\0';

		char *p = line;
		while (*p == ' ' || *p == '\t')
			p++;
		if (*p == '\0')
			continue;                /* empty line */

		/* history feature: "!!" re-runs the most recent command */
		if (strcmp(p, "!!") == 0) {
			if (history[0] == '\0') {
				printf("No commands in history.\n");
				continue;
			}
			strcpy(line, history);
			printf("%s\n", line);    /* echo the command being repeated */
		} else {
			strcpy(history, p);
		}

		int n = parse(line, args);
		if (n == 0)
			continue;

		/* built-in commands (must run in the shell itself, not a child) */
		if (strcmp(args[0], "exit") == 0) {
			should_run = 0;
			continue;
		}
		if (strcmp(args[0], "cd") == 0) {
			const char *dir = args[1] ? args[1] : getenv("HOME");
			if (dir == NULL || chdir(dir) < 0)
				perror("cd");
			continue;
		}

		/* trailing '&' means: do not wait for the child */
		int background = 0;
		if (strcmp(args[n - 1], "&") == 0) {
			background = 1;
			args[--n] = NULL;
			if (n == 0)
				continue;
		} else {
			size_t l = strlen(args[n - 1]);
			if (l > 1 && args[n - 1][l - 1] == '&') {
				args[n - 1][l - 1] = '\0';
				background = 1;
			}
		}

		int bar = find_token(args, "|");
		if (bar >= 0) {
			args[bar] = NULL;
			if (args[0] == NULL || args[bar + 1] == NULL) {
				fprintf(stderr, "osh: syntax error near '|'\n");
				continue;
			}
			run_pipe(args, args + bar + 1, background);
		} else {
			run_simple(args, background);
		}
	}

	return 0;
}
