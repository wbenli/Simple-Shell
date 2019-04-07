#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

const int INIT_CMD_SIZE = 16;
const int bufferSize = 512;

int nextCommand();
void inputStrToArr(char* inputStr, char*** toReturn);
char* getInput(char* buffer);
int processInput(char** command);
void  cd_command(char* filename);
void  pwd_command();
char* gnu_getcwd();

int main(int argc, char *argv[]){
	//TODO: Read this from terminal
	char inputStr[] = "/bin/date -u";

	return nextCommand();
}

int nextCommand() {	
	char* inputBuffer = malloc( sizeof(char) * 512);
	getInput(inputBuffer);	
	inputBuffer[strcspn(inputBuffer, "\n")] = 0;

	char **command = NULL;
	inputStrToArr(inputBuffer,&command);
	
	processInput(command);

	nextCommand();
}

char* getInput(char* buffer) {
	printf("sshell$ ");
	fgets(buffer, bufferSize + 1, stdin);
	return buffer;
}

int processInput(char ** command) {

	char *args[] = { command[0], *command, NULL };
	int retval;
	
	if (fork() != 0) {
		/* This is the Parent*/
		int status;
		waitpid(-1, &status, 0);
		//TODO: Doens't print full command
		fprintf(stderr, "+ completed ");

		fprintf(stderr, "'");
		for (int i = 0; command[i] != NULL; i++) {
			if (i > 0) fprintf(stderr, " ");
			fprintf(stderr, "%s", command[i]);
		}
		fprintf(stderr,"' [%i]\n", status);
	} else {
		execv(command[0],args);
		perror("execv");
		exit(1);
	}

	return EXIT_SUCCESS;

}

void inputStrToArr(char* inputStr, char*** toReturn) {
	const char *s = " ";
	int size = INIT_CMD_SIZE;

	*toReturn = malloc( sizeof(char *) * size);

	char *token;
	token = strtok(inputStr, s);
	for (int i = 0; token != NULL; i++) {
		(*toReturn)[i] = malloc(strlen(token));

		(*toReturn)[i] = token;
	
		//Reallocate size of array if necessary
		//TODO: Test this
		if (i == ( size-1 )) 
		{
			//printf("filled %i of %i elements\n", i+1, size);

			char **newToReturn = realloc(*toReturn, sizeof(char *) * size*2);
			*toReturn = newToReturn;
		}

		token = strtok(0,s);
	}

	return;
}

void cd_command(char* path){
	if(chdir(path) != 0)
		perror("cd");
} 

void pwd_command(){
	char* buffer = NULL;
	buffer = gnu_getcwd();
	fprintf(stdout, "%s\n", buffer);

}

char* gnu_getcwd(){
  size_t size = 100;

  while (1)
    {
      char *buffer = (char *) malloc (size);
      if (getcwd (buffer, size) == buffer)
        return buffer;
      free (buffer);
      if (errno != ERANGE)
        return 0;
      size *= 2;
    }	
}


