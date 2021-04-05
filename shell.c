#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void main(int argc,char* argv[]){
	char path[]="/home/braude/",command[50];
	int pid;
	while('1'){
   	 	printf("Enter shell1 to run linux commands without parameters\n");
   	 	printf("Enter shell2 to run linux commands with parameters\n");
   		printf("Enter shell3 to run commands to file editing\n");
    	printf("Shell$** ");
		scanf("%s",command);
    	if(strcmp(command,"Exit")==0)
        	return;
		if((pid=fork())==0){
			execl(strcat(path,command),command,NULL);
			printf("Not Supported\n");
			exit(1);
			}
		wait();
	}
}
