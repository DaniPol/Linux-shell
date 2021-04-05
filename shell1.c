#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void main(int argc, char* argv[]) {
	char path[256] = "/bin/", command[50];
	int i , pid;
	while ('1') {
		i=0;
		printf("Shell1$**");
		fgets(command, 50, stdin);
		while(command[i]!='\n')
			i++;
		command[i]='\0';
		if (strcmp(command,"Esc") == 0)
			return;
		if (pid=fork() == 0) {
			execl(strcat(path, command), command, 0);
			printf("Not supported\n");
			exit(1);
			}
			wait();
		}
	}

