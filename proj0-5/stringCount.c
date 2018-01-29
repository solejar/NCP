#include<stdio.h>
#include<string.h>

struct substrLink
{
	char val;
	 	
};

int main(int argc, char ** argv){
	//let's read in input substrings, and put them into a search tree of sorts
        struct substrLink inputString[26];

        int sysCallImplementation,lastString;
        if(strcmp(argv[argc-1],"--systemcalls")==0){
                sysCallImplementation = 1;
                lastString = argc-2;
		printf("Supposedly, %s = --systemcalls",argv[argc-1]);
        }else{
                sysCallImplementation = 0;
                lastString = argc-1;
		printf("Supposedly, %s != --systemcalls",argv[argc-1]);
        }
        
        for (int i = 2;i<=lastString;i++){
                char * temp = argv[i];
    		printf("read in substring of: %s \n",temp);
	}	 
	//let's open up the file and read in characters (need to decide what implementation is best)
	char *fileName = argv[1];
	FILE *fp;	
	fp = fopen(fileName, "r");

	return 0;
}
