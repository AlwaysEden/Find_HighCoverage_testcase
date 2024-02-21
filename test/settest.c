#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>

struct files{
	int size;
	char filename[20];
	int number;
};

int compare(const void *a, const void *b)  //내림차순 정렬
{
    struct files *pa = (struct files*)a;
    struct files *pb = (struct files*)b;

    if(pa->size < pb->size)
        return 1;
    else if(pa->size > pb->size)
        return -1;
    else
    return 0;
}

const int FILE_NUM = 5542;
struct files file[5543];

void* makeset_ascend(void *idx){
	int start = *((int *)idx);
	char case1[100];
	char case2[100];
	char case3[100];
	char case4[100];
	char case5[100];
	char case6[100];
	char case7[100];
	char case8[100];

	char resultcmd[100];
	int a = start;
		sprintf(case1,"./t%d.sh",file[a].number);
		for(int b=a+300; b<=FILE_NUM; b+=10){
			sprintf(case2,"./t%d.sh",file[b].number);
			for(int c=b+300; c<=FILE_NUM; c+=10){
				sprintf(case3,"./t%d.sh",file[c].number);
				for(int d=c+300; d<=FILE_NUM; d+=10){
					sprintf(case4,"./t%d.sh",file[d].number);
					for(int e=d+300; e<=FILE_NUM; e+=10){
						sprintf(case5,"./t%d.sh",file[e].number);
						for(int f=e+300; f<=FILE_NUM; f+=10){
							sprintf(case6,"./t%d.sh", file[f].number);
							for(int g=f+300; g<=FILE_NUM; g+=10){
								sprintf(case7,"./t%d.sh",file[g].number);
								for(int h=g+300; h <=FILE_NUM; h+=10){
                                                                sprintf(case8,"./t%d.sh",file[h].number);

								
								system(case1);
								system(case2);
								system(case3);
								system(case4);
								system(case5);
								system(case6);
								system(case7);
								system(case8);
								chdir("../bin");
								sprintf(resultcmd,"gcov -b replace > ./2.result_branch/case%d,%d,%d,%d,%d,%d,%d,%d.txt",file[a].number,file[b].number,file[c].number,file[d].number,file[e].number,file[f].number,file[g].number, file[h].number);
								system(resultcmd);
								system("rm replace.gcda");
								chdir("../test");
								}
							}
						}
					}
				}
			}
		}
	
	
}


void* makeset_desc(void *idx){
	int start = *(int *)idx;
	char case1[100];
	char case2[100];
	char case3[100];
	char case4[100];
	char case5[100];
	char case6[100];
	char case7[100];
	char case8[100];

	char resultcmd[100];
	int a = start;	
	sprintf(case1,"./t%d.sh",file[a].number);
		for(int b=a-300; b>=0; b-=10){
			sprintf(case2,"./t%d.sh",file[b].number);
			for(int c=b-300; c >=0; c-=10){
				sprintf(case3,"./t%d.sh",file[c].number);
				for(int d=c-300; d>=0; d-=10){
					sprintf(case4,"./t%d.sh",file[d].number);
					for(int e=d-300; e>=0; e-=10){
						sprintf(case5,"./t%d.sh",file[e].number);
						for(int f=e-300; f>=0; f-=10){
							sprintf(case6,"./t%d.sh", file[f].number);
							for(int g=f-300; g >= 0; g-=10){
								sprintf(case7,"./t%d.sh",file[g].number);
								for(int h=g-300; h >=0; h-=10){
								sprintf(case8,"./t%d.sh",file[h].number);	
								
								system(case1);
								system(case2);
								system(case3);
								system(case4);
								system(case5);
								system(case6);
								system(case7);
								system(case8);
								chdir("../bin");
								sprintf(resultcmd,"gcov -b replace > ./2.result_branch/case%d,%d,%d,%d,%d,%d,%d,%d.txt",file[a].number,file[b].number,file[c].number,file[d].number,file[e].number,file[f].number,file[g].number, file[h].number);
								system(resultcmd);
								system("rm replace.gcda");
								chdir("../test");
								}
							}
						}
					}
				}
			}
		}
	
}

int main(){
	struct stat state;
	
	for(int i = 1; i <= FILE_NUM; i++){
		sprintf(file[i].filename, "../bin/1.gcovfile_branch/testcase%d.gcov",i);
		if(stat(file[i].filename, &state) == -1){
			perror("Error stat(): ");
			continue;
		}
		file[i].number = i;
		file[i].size = state.st_size;	
		printf("%d: %s %d\n",i,file[i].filename, file[i].size); 
	}

	qsort(file,9,sizeof(struct files),compare);

	/*for(int i = 1; i <= 9; i++){
		printf("%d: %s %d\n",i,file[i].filename, file[i].size); 
	}*/
	
	pthread_t tid[5542];

	for(int i = 0; i < 2500; i++){
		int *arg = malloc(sizeof(int));
		*arg = i+1;
		pthread_create(&tid[i], NULL, makeset_ascend, arg);
		free(arg);
	}
	
	for(int i = 5541; i >= 2500; i--){
		int *arg = malloc(sizeof(int));
		*arg = i-1;
		pthread_create(&tid[i], NULL, makeset_desc, arg);
		free(arg);
	}

	for(int i = 0; i < 5542; i++){
		pthread_join(tid[i], NULL);
	}
	
}
