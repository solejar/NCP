#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

typedef struct listItem
{
	char * val;
	int intVal;
	struct listItem * next;

} listItem;

listItem * listItemCreator(char * itemVal, int intVal){
	listItem* newNode = malloc(sizeof(listItem));
	newNode->val = itemVal;
	newNode->intVal = intVal;
	newNode->next = NULL;

	return newNode;
}

void listItemDestroy(listItem* item){
	//printf("called for item with val of: %s\n",item->val);
	free(item);
}

void listDestroy(listItem* head){
	if(head->next){
		listDestroy(head->next);
		
	}

	listItemDestroy(head);

	return;
}

int searchSubstr(char * document,char* substr){
	//printf("called with doc: %s, and substr: %s\n",document,substr);
	listItem * head;
	listItem * oldItem;
	listItem * currItem;

	char * dummy = "hello";

	head = listItemCreator(dummy,0);
	oldItem = head;

	char * c = substr; //iterator for the substr
	char *doc; //iterator for the search arr
	
	doc = document;
	int index = 0;

	while(doc!=NULL&& *doc!='\0'){ //first pass, create linked list of 'hits'
	
		if(*doc==*c){
			//printf("char: %c, index: %d\n",*doc,index);
			
			currItem = listItemCreator(dummy,index);
			oldItem->next = currItem;
			oldItem = currItem;
		}

		//printf("one iteration of searching, index: %d\n", index);
		/*if(index+1>=length){
			printf("gonna break the loop\n");
			break;
		}else{
			//printf("loop all good!\n");
		}*/
		doc++;
		index++;
		
	}
	//printf("successfully initialized search list\n");

	int count = 0;
	c++;
	doc = document;
	currItem = head;

	while(c!=NULL&& *c!='\0'){ //then for rest of substr, iterate through list instead of whole doc
		//printf("char: %c\n",*c);
		while(currItem->next!=NULL){ //increment if this node matches
			oldItem = currItem;
			currItem = oldItem->next;

			//printf("%c\n",doc[(currItem->intVal)+1]);
			if(doc[(currItem->intVal)+1]==*c){
				currItem->intVal++;

			}else{ //if this node was a failure, remove it
				listItem * next = currItem->next;
				oldItem->next = next;

				listItem * nonExistent = currItem;
				listItemDestroy(nonExistent);

				//printf("destroyed a list elem\n");

				currItem = oldItem;
				
			}
			
		}
		
		currItem = head;
		c++;

	}
	
	while(currItem->next!=NULL){
		currItem = currItem->next;
		count++;
	};

	listDestroy(head);

	return count;
}


int main(int argc, char ** argv){

    int sysCallImplementation,lastString;
    if(strcmp(argv[argc-1],"--systemcalls")==0){
        sysCallImplementation = 1;
        lastString = argc-2;

    }else{
        sysCallImplementation = 0;
        lastString = argc-1;
    }
    
    listItem * oldItem;
    listItem * currItem;
    listItem * head;
    char * temp = argv[2];

    head = listItemCreator(argv[2],0);
    oldItem = head;

    int i;
    for (i = 3;i<=lastString;i++){
        
        char * temp = argv[i];
		
		currItem = listItemCreator(temp,0);
		oldItem->next = currItem; 
		oldItem = currItem;
	}	 

	///let's open up the file and read in characters (need to decide what implementation is best)
	char *fileName = argv[1];
	
	FILE *fp;	
	fp = fopen(fileName, "rb");
	if(!fp) perror(fileName),exit(1);

	fseek(fp, 0L, SEEK_END);
	int sz = ftell(fp);
	rewind(fp);
	
	char * arr = calloc(1,sz+1);
	if(!arr) 
		fclose(fp),listDestroy(head),fputs("memory alloc fails",stderr),exit(1);

	if(sysCallImplementation){
		fclose(fp);
		int fd = open(fileName,O_RDONLY);
		if(fd<0){
			strerror(errno);
			exit(1);
		}

		int i;
		for(i = 0;i<sz;i++){
			
			if(read(fd,(arr+i),1)<0){
				if(arr) free(arr);
				listDestroy(head);
				fputs("syscall reads failed\n",stderr);
				exit(1);
			}			
		}		
		
	}else{

		if(1!=fread(arr,sz,1,fp))
			fclose(fp),free(arr),listDestroy(head),fputs("entire read fails",stderr),exit(1);

		fclose(fp);

	}
	
	currItem = listItemCreator("dummy",0);
	currItem->next = head;

	while(currItem->next!=NULL){
		currItem = currItem->next;
		printf("%d\n",searchSubstr(arr,currItem->val));
		
	}

	if(head) listDestroy(head);
	if(arr) free(arr);
	return 0;
}
