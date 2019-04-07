#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

const int INIT_CMD_SIZE = 16;

void inputStrToArr(char* inputStr, char ***toReturn);
void  cd_command(char* filename);
void  pwd_command();
char* gnu_getcwd();

int main(int argc, char *argv[]){

	TODO: Read this from terminal
	char inputStr[] = "/bin/date -u";

	char **command = NULL;
	inputStrToArr(inputStr,&command);

	char *args[] = { command[0], "-u", NULL };
	int retval;
	
	if (fork() != 0) {
		/* This is the Parent*/
		int status;
		waitpid(-1, &status, 0);
	} else {
		execv(command[0],args);
		perror("execv");
		exit(1);
	}

	return EXIT_SUCCESS;
}

void inputStrToArr(char* inputStr, char ***toReturn) {
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
			printf("filled %i of %i elements\n", i+1, size);

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


