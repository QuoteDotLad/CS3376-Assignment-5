//file : TwoPipesThreeChildren.cpp
//Author : Chance Ball
//Date : 4/4/17
//Purpose : CS3376 Assignment 5
//Description : Uses three children to execute commands

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(int argc, char **argv){
 int childOnepid, childTwopid, childThreepid;
  
 char *cat_args[] = {"ls", "-ltr", NULL};
 char *grep_args[] = {"grep", "3376", NULL};
 char *wc_args[] = {"wc", "-l", NULL};
 // create two pipes to send the output of "ls" process to "grep" process and then to "wc" process
 int pipeOne[2];
 int pipeTwo[2];

pipe(pipeOne);
pipe(pipeTwo);
 
 // fork the first child (to execute cat)
if((childOnepid = fork()) == -1){
     perror("Error creating a child process");
     exit(1);
   }
   if(childOnepid == 0) { //First child
      // close all pipes (very important!); end we're using was safely copied
      close(pipeOne[0]);
      dup2(pipeOne[1],1); //Redirect standard output to pipeOne's write end
      close(pipeOne[1]);
       execvp(*cat_args, cat_args);
   }
if((childTwopid = fork()) == -1){
     perror("Error creating child process 2");
     exit(1);
   }
   if(childTwopid == 0){ //Second child
   	   close(pipeOne[1]);
	   dup2(pipeOne[0], 0); //redirect standard input to pipeOne's read end
	   //Closing all pipes again

	   close(pipeOne[0]);
	   close(pipeTwo[0]);
	   dup2(pipeTwo[1],1); //Redirect standard output to PipeTwo's write end
	   close(pipeTwo[1]);
	    execvp(*grep_args, grep_args);
	  }
    close(pipeOne[1]);
    close(pipeOne[0]);
   
if((childThreepid = fork()) == -1){
     perror("Error creating child process 3");
     exit(1);
   }
   if(childThreepid == 0){ //Third child
	close(pipeTwo[1]);
	dup2(pipeTwo[0],0); //Redirecting standard input to pipeTwo's read
	close(pipeTwo[0]);
	execvp(*wc_args, wc_args);
   }
close(pipeTwo[1]);
close(pipeTwo[0]);
return(0);
}
