#include<stdio.h>
#include<string.h>

typedef struct node
{
	char val;
	struct node * next;
	 	
} substrNode;

int main(int argc, char ** argv){
	//let's read in input substrings, and put them into a search tree of sorts
        substrNode inputString[26];

	for(int i = 0;i<26;i++){
		inputString[i].val = 97+i; //this range represents all 26 lowercase letters 
                //printf("Just added %c\n",inputString[i].val);
	}

        int sysCallImplementation,lastString;
        if(strcmp(argv[argc-1],"--systemcalls")==0){
                sysCallImplementation = 1;
                lastString = argc-2;
		printf("Supposedly, %s = --systemcalls\n",argv[argc-1]);
        }else{
                sysCallImplementation = 0;
                lastString = argc-1;
		printf("Supposedly, %s != --systemcalls\n",argv[argc-1]);
        }
        
        for (int i = 1;i<=lastString;i++){
                char * temp = argv[i];
    		printf("read in substring of: %s \n",temp);
	}	 
	//let's open up the file and read in characters (need to decide what implementation is best)
	char *fileName = argv[1];
	FILE *fp;	
	fp = fopen(fileName, "r");

	return 0;
}
