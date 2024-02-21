#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
	DIR * dp;
	struct dirent *dir;
	FILE *fp;
	dp = opendir("./2.result");
	char line[256];
	int biggest = 0;
	char biggest_name[256];
	char filePath[256];
	chdir("./2.result");

	while(dir = readdir(dp)){
		fp = fopen(dir->d_name,"rb");
		if(fp==NULL){
			fprintf(stderr,"ERROR fopen()");
			continue;
		}
		while (fgets(line, sizeof(line), fp)) {
        		if (strstr(line, "Lines executed:") != NULL) {
            			int coverage;
            			if (sscanf(line, "Lines executed: %d%%", &coverage) == 1) {
					if(coverage > biggest){
						biggest = coverage;
						strcpy(biggest_name,dir->d_name);
					}
                			break; // 원하는 정보를 찾았으므로 종료
            			}
        		}
    		}
		fclose(fp);
	}

	printf("Biggest File: %s, %d",biggest_name, biggest);
}
