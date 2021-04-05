#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void main(int argc, char* argv[]) {
	char path[256] = "/bin/", str[50], command[50], parameter1[50], parameter2[50],parameter3[50];
	int i,j, pid, counter;
	while ('1') {
		i = 0;
		j=0;
		counter = 1;
		printf("Shell2$**");
		fgets(str, 50, stdin);
		while (str[i] != '\n') {
			if (str[i] == ' ') {
				counter++;
				j=-1;
			}
			else {
				if (counter == 1) {
					command[j] = str[i];
					command[j + 1] = '\0';
				}
				if (counter == 2) {
					parameter1[j] = str[i];
					parameter1[j+1] = '\0';
				}
				if (counter == 3) {
					parameter2[j] = str[i];
					parameter2[j+1] = '\0';
				}
				if (counter == 4) {
					parameter3[j] = str[i];
					parameter3[j+1] = '\0';
				}
			}	
			i++;
			j++;
		}
		if (counter == 1 && strcmp(command, "Esc") == 0)
			return;
		if (pid = fork() == 0) {
			if (counter == 1) {
				execl(strcat(path, command), command, NULL);
				printf("Not Supported\n");
				exit(1);
			}
			if (counter == 2) {
				execl(strcat(path, command), command,parameter1, NULL);
				printf("Not Supported\n");
				exit(1);
			}
			if (counter == 3) {
				execl(strcat(path, command), command, parameter1,parameter2, NULL);
				printf("Not Supported\n");
				exit(1);
			}
			if (counter == 4) {
				execl(strcat(path, command), command, parameter1,parameter2,parameter3, NULL);
				printf("Not Supported\n");
				exit(1);
			}
		}
		else {
			wait();
		}
	}
}


