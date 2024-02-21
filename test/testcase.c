#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

const int TOTAL_FILE_NO = 3;
int pid;


int main()
{
	char shellcmd[1024];
	int status;
	for(int i = 1; i <= TOTAL_FILE_NO; i++){
		sprintf(shellcmd,"./t%d.sh",i);

		//system(shellcmd);
		pid = fork();
		if(pid == 0){
			if(execlp(shellcmd, shellcmd,(char *)NULL) == -1){
				perror("Error shell execl(): ");
				exit(1);
			}
		}else{
			wait(&status);
		}
		
		pid = fork();
		if(pid == 0){
			if(execlp("../bin/", "gcov -b -i replace",(char *)NULL) == -1){
				perror("Error gcov execl(): ");
				exit(1);
			}
		}else{
			wait(&status);
		}
	/*	
		pid = fork();
		if(pid == 0){
			if(execl("../bin/", "gcov", "-b", "-i", "replace",(char *)NULL) == -1){
				perror("Error gcov execl(): ");
				exit(1);
			}
		}else{
			wait(&status);
		}
			
		if(system("mkdir ../bin/gcovfile") == -1){
			perror("ERROR mkdir system(): ");
			exit(1);
		}
		
		if(system("mv ../bin/replace.c.gcov ../bin/gcovfile/") == -1){
			perror("ERROR mv system(): ");
			exit(1);
		}
		
		if(system("mv ../bin/replace.c.gcov ../bin/testcase1.gcov") == -1){
			perror("ERROR rename system(): ");
			exit(1);
		}
	*/	

		//printf("%s\n",filename);
	}	
}
