#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
int main(){
	DIR *dir;
    struct dirent *lsdir;
	char *li;
	struct dirent **namelist;
	int n;

	n = scandir(".", &namelist, 0, alphasort);
	if (n < 0) perror("scandir");
	printf("%d\n",n);
	else {
		while((n--)-3) {
			printf("%s\n", namelist[n]->d_name);
			free(namelist[n]);
		}
		free(namelist);
	}

	//FILE *arq;
	//arq = fopen("/home/user/20170023696-LP2-ProvaPratica1/help.txt", "w");
	//if(arq == NULL) printf("nao foi possivel abrir o arquivo\n");
	/*
	dir = opendir("/home/user/20170023696-LP2-ProvaPratica1/reqs");
	if(dir == NULL) printf("nao foi possivel abrir diretorio\n");

	while ( ( lsdir = readdir(dir) ) != NULL );
	strcpy(li, lsdir->d_name);

	//fclose(arq);

	//arq = fopen("/home/user/20170023696-LP2-ProvaPratica1/help.txt", "r");
	//if(arq == NULL) printf("nao foi possivel abrir o arquivo");

	//while(fgets(li, 28, arq) != NULL);
    //printf("%s\n",li );
    int arqcount = 0;
    int i;
    /*
    for(i=0; i < sizeof(lsdir->d_name); i++){
    	if(lsdir->d_name[i] == ".") arqcount++;
    }
    
    printf("%ld\n", sizeof(lsdir->d_name));
    
    strcpy(li, lsdir->d_name);
    /*
    printf("%c\n", li[0]);
    
    closedir(dir);
    */
    //fclose(arq);
    	//system("pause");
	return 0;
}