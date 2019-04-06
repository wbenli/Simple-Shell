#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	char *cmd = "/bin/date -u";

	//TODO: split command by whitespace
	char *command = "/bin/date";
	char *args[] = { command, "-u", NULL };
	
	int retval;
	
	if (fork() != 0) {
		/* This is the Parent*/
		int status;
		waitpid(-1, &status, 0);
	} else {
		execv(command,args);
		perror("execv");
		exit(1);
	}

	return EXIT_SUCCESS;
}
