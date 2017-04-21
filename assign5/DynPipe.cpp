#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <libgen.h>
void pipeArgs(char **);
int main(int argc, char** argv) {
	if(argc < 3)
	{
	printf("Usage: %s, [<string>...]\n", argv[1]);
	return(1);	
	}
	else if(argc > 6)
	{
	printf("Too many inputs, there is a maximum of 5 allowed.\n");
	return(1);
	}
	char *cmd_args[argc]; //Holds all our command line arguments minus the execution string
	cmd_args[argc] = NULL;
	int k = 1;
	for(int i = 0; i < argc; i++)
	{
	cmd_args[i] = argv[k];
	//printf("cmd_args[%d] : %s", i, cmd_args[i]);
	k++;
	}
	pipeArgs(cmd_args);
	return(0);
}
void pipeArgs(char **cmd_args)
{
	int pipes[2]; //Creating our pipe
	int pid;
	int fd_in = 0; //Saving the 0 descriptor to make sure inputs are saved later

	while(*cmd_args != NULL)
	{
	pipe(pipes);
		if((pid = fork()) == -1) {
		perror("Error during fork");
		exit(0);
		}
		
		else if(pid == 0) {
		dup2(fd_in, 0); //Change next input in relation to the old input
			printf("OHOOH");
			if(*(cmd_args + 1) != NULL) { 
			dup2(pipes[1], 1);
			}

		close(pipes[0]);
		execvp((cmd_args)[0], cmd_args);
		exit(0);
		}
		else
		{
		wait(NULL); //Waiting for a child with pid to terminate
		close(pipes[1]);
		fd_in = pipes[0];
		cmd_args++;
		}
	}
}
