#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char ** argv){
if(argc < 3)
{
printf("Usage : %s, [<string>...]\n", argv[1]);
return(1);
}
else if(argc > 6)
{
printf("Too many inputs, maximum 5 allowed.\n");
return(1);
}
char *args[argc];
for(int i = 1; i < argc; i++)
{
args[i] = argv[i];
printf("%s\n", args[i]);
}
return(0);
}
