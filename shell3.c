#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void main(int argc, char* argv[]) {
	int i, j, s, counter, fd1, fd2, fd3, rbytes1 = 1, rbytes2 = 1, wbytes;
	char str[50], command[50], parameter1[50], parameter2[50], parameter3[50];
	char path[256] = "/home/braude/", file1[50], file2[50], file3[50];
	char buff1[101], buff2[101], word[201];
	int max1, max2;
	int flag = 0, error;
	while ('1') {
		i = 0;//restart all used for reading and writing
		j = 0;
		counter = 1;
		rbytes1 = 1;
		rbytes2 = 1;
		max1 = 0;
		max2 = 0;
		flag = 0;
		error = 0;
		printf("Shell3$**");
		fgets(str, 50, stdin);
		while (str[i] != '\n') {//scan command and parameters
			if (str[i] == ' ') {
				counter++;
				j = -1;
			}
			else {
				if (counter == 1) {
					command[j] = str[i];
					command[j + 1] = '\0';
				}
				if (counter == 2) {
					parameter1[j] = str[i];
					parameter1[j + 1] = '\0';
				}
				if (counter == 3) {
					parameter2[j] = str[i];
					parameter2[j + 1] = '\0';
				}if (counter == 4) {
					parameter3[j] = str[i];
					parameter3[j + 1] = '\0';
				}
			}
			i++;
			j++;
		}

		if (strcmp(command, "Esc") == 0 && counter == 1)//if the user want to got back to shell
			return;
		if (strcmp(command, "Merge") == 0) {//merge
			if (counter > 4 || counter < 3) {
				printf("Wrong number of arguments\n");
			}
			else {
				strcpy(file1, path);//open first file                             //open files
				if ((fd1 = open(strcat(file1, parameter1), O_RDONLY)) == -1) {
					printf("cant open %s\n", parameter1);
					error = 1;

				}
				strcpy(file2, path);//open second file
				if ((fd2 = open(strcat(file2, parameter2), O_RDONLY)) == -1) {
					printf("cant open %s\n", parameter2);
					error = 1;

				}
				if (counter == 4) {//open third file
					strcpy(file3, path);
					if ((fd3 = open(strcat(file3, parameter3), O_WRONLY | O_CREAT, 0667)) == -1) {
						printf("cant open %s\n", parameter3);
						error = 1;

					}
				}//end of open files
				if (error != 1) {
					while (rbytes1 != 0 && rbytes2 != 0) {//check if there is something to read from a file
						if (rbytes1 != 0) {// read if first file is not empty
							if ((rbytes1 = read(fd1, buff1, 100)) == -1) {
								printf("cant read form %s\n", parameter1);
								break;

							}
						}
						buff1[rbytes1] = '\0';//end of read files
						if (rbytes2 != 0) {// read if second file is not empty
							if ((rbytes2 = read(fd2, buff2, 100)) == -1) {
								printf("cant read form %s\n", parameter2);
								break;

							}
						}
						buff2[rbytes2] = '\0';//end of read files

						if (rbytes1 == 0 && rbytes2 == 0) {//if both files are empty
							close(fd1);
							close(fd2);
							if (counter == 4)
								close(fd3);
							break;
						}
						i = 0;//restart all indexes
						j = 0;
						s = 0;
						while (buff1[i] != '\0' || buff2[j] != '\0') {//while all that had been read is not written
							if (buff1[i] != '\0') {// if not at the end of buff1
								while (buff1[i] != ' ') { //read a word from buff1
									if (buff1[i] != '\n') {
										word[s] = buff1[i];
										s++;
										i++;
									}
									else {
										word[s] = ' ';
										s++;
										i++;
										break;

									}
								}
								if (buff1[i] == ' ') {
									word[s] = buff1[i];
									s++;
									while (buff1[i] == ' ')
										i++;
								}
							}//end read a word form buff1
							if (buff2[j] != '\0') {// if not at the end of buff1
								while (buff2[j] != ' ') {//read a word from buff1
									if (buff2[j] != '\n') {
										word[s] = buff2[j];
										s++;
										j++;
									}
									else {
										word[s] = ' ';
										s++;
										j++;
										break;
									}
								}
								if (buff2[j] == ' ') {
									word[s] = buff2[j];
									s++;
									while (buff2[j] == ' ')
										j++;
								}
							}//end read a word from buff2

						}//end read from two buffs
						word[s] = '\n';
						word[s + 1] = '\0';
						if (counter == 3) {//write to screen
							if ((wbytes = write(1, word, strlen(word))) == -1) {
								printf("cant write to screen\n");

							}
							if (strlen(word) != wbytes) {
								printf("didnt write all that has been read\n");

							}
						}

						if (counter == 4) {//write to a file
							if ((wbytes = write(fd3, word, strlen(word))) == -1) {
								printf("cant write to %s\n", parameter3);

							}
							if (strlen(word) != wbytes) {
								printf("didnt write all that has been read\n");

							}
						}
					}//end reading from files
				}
			}
			flag = 1;
		}//end of merge
		if (strcmp(command, "Find_Max") == 0) {//Find Max
			if (counter != 3) {
				printf("Wrong number of argumnets\n");
			}
			else {
				strcpy(file1, path);//open first file
				if ((fd1 = open(strcat(file1, parameter1), O_RDONLY)) == -1) {
					printf("cant open %s\n", parameter1);
					error = 1;
				}
				strcpy(file2, path);//open second file
				if ((fd2 = open(strcat(file2, parameter2), O_RDONLY)) == -1) {
					printf("cant open %s\n", parameter2);
					error = 1;
				}
				if (error != 1) {
					while (rbytes1 != 0) {
						if (rbytes1 != 0) {// read if first file is not empty
							if ((rbytes1 = read(fd1, buff1, 100)) == -1) {
								printf("cant read form %s\n", parameter1);
								break;
							}
							max1 += rbytes1;
						}
					}
					while (rbytes2 != 0) {
						if (rbytes2 != 0) {// read if first file is not empty
							if ((rbytes2 = read(fd2, buff2, 100)) == -1) {
								printf("cant read form %s\n", parameter2);
								break;
							}
							max2 += rbytes2;
						}
					}
					close(fd1);
					close(fd2);
					if (max1 >= max2)
						printf("%s\n", parameter1);
					else
						printf("%s\n", parameter2);
				}
			}
			flag = 1;
		}//end of Find Max
		if (strcmp(command, "Size") == 0) {//size
			if (counter != 2)
				printf("Wrong number of arguments\n");
			else {
				strcpy(file1, path);//open first file
				if ((fd1 = open(strcat(file1, parameter1), O_RDONLY)) == -1) {
					printf("cant open %s\n", parameter1);
					error = 1;
				}
				if (error != 1) {
					while (rbytes1 != 0) {
						if (rbytes1 != 0) {// read if first file is not empty
							if ((rbytes1 = read(fd1, buff1, 100)) == -1) {
								printf("cant read form %s\n", parameter1);
								break;
							}
							max1 += rbytes1;
						}
					}
					close(fd1);
					printf("%d\n", max1);
				}
			}
			flag = 1;
		}//end of size
		if (strcmp(command, "Delete") == 0) {//Delete
			if (counter != 2)
				printf("wrong number of arguments\n");
			else {
				int remove = 0;
				strcpy(file1, path);
				if ((remove = unlink(strcat(file1, parameter1))) == -1)
					printf("cant remove %s\n", parameter1);
			}
			flag = 1;
		}//end of Delete
		if (flag == 0)//if there is no such command
			printf("Not Supported\n");
	}//while(1)
}
