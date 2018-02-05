#include<stdio.h>
#include<string.h>

typedef struct node
{
	char val;
//	int doesExist;
//come up with linked list to denote children members
	//struct node next[26];
	struct node * a;
	struct node * b;	 	
	struct node * c;
	struct node * d;
	struct node * e;
	struct node * f;
	struct node * g;
	struct node * h;
	struct node * i;
	struct node * j;
	struct node * k;
	struct node * l;
	struct node * m;
	struct node * n;
	struct node * o;
	struct node * p;
	struct node * q;
	struct node * r;
	struct node * s;
	struct node * t;
	struct node * u;
	struct node * v;
	struct node * w;
	struct node * x;
	struct node * y;
	struct node * z;

} substrNode;

/*
typedef struct listElement
{
	
} listElem;*/

substrNode* substrNodeCreator(char nodeVal){
	substrNode* newNode = malloc(sizeof(substrNode));
	newNode->val = nodeVal;
//	newNode->doesExist = 0;

	newNode->a = malloc(sizeof(substrNode));
	newNode->b = malloc(sizeof(substrNode));
	newNode->c = malloc(sizeof(substrNode));
	newNode->d = malloc(sizeof(substrNode));
	newNode->e = malloc(sizeof(substrNode));
	newNode->f = malloc(sizeof(substrNode));
	newNode->g = malloc(sizeof(substrNode));
	newNode->h = malloc(sizeof(substrNode));
	newNode->i = malloc(sizeof(substrNode));
	newNode->j = malloc(sizeof(substrNode));
	newNode->k = malloc(sizeof(substrNode));
	newNode->l = malloc(sizeof(substrNode));
	newNode->m = malloc(sizeof(substrNode));
	newNode->n = malloc(sizeof(substrNode));
	newNode->o = malloc(sizeof(substrNode));
	newNode->p = malloc(sizeof(substrNode));
	newNode->q = malloc(sizeof(substrNode));
	newNode->s = malloc(sizeof(substrNode));
	newNode->t = malloc(sizeof(substrNode));
	newNode->u = malloc(sizeof(substrNode));
	newNode->v = malloc(sizeof(substrNode));
	newNode->w = malloc(sizeof(substrNode));
	newNode->x = malloc(sizeof(substrNode));
	newNode->y = malloc(sizeof(substrNode));
	newNode->z = malloc(sizeof(substrNode));
};

void substrNodeDestroyer(substrNode*){
	//need to recursively free allocated memory somehow
};

void populateNode (substrNode* source, char newChar){
	switch(newChar){
		case 'a':
			source->a = substrNodeCreator('a');
			break;
		case 'b':
			source->b = substrNodeCreator('b');
			break;
		case 'c':
			source->c = substrNodeCreator('c');
			break;
		case 'd':
			source->d = substrNodeCreator('d');
			break;
		case 'e':
			source->e = substrNodeCreator('e');
			break;
		case 'f':
			source->f = substrNodeCreator('f');
			break;
		case 'g':
			source->g = substrNodeCreator('g');
			break;
		case 'h':
			source->h = substrNodeCreator('h');
			break;
		case 'i':
			source->i = substrNodeCreator('i');
			break;
		case 'j':
			source->j = substrNodeCreator('j');
			break;
		case 'k':
			source->k = substrNodeCreator('k');
			break;
		case 'l':
			source->l = substrNodeCreator('l');
			break;
		case 'm':
			source->m = substrNodeCreator('m');
			break;
		case 'n':
			source->n = substrNodeCreator('n');
			break;
		case 'o':
			source->o = substrNodeCreator('o');
			break;
		case 'p':
			source->p = substrNodeCreator('p');
			break;
		case 'q':
			source->q = substrNodeCreator('q');
			break;
		case 'r':
			source->r = substrNodeCreator('r');
			break;
		case 's':
			source->s = substrNodeCreator('s');
			break;
		case 't':
			source->t = substrNodeCreator('t');
			break;
		case 'u':
			source->a = substrNodeCreator('a');
			break;
		default:

	}
}; 

int main(int argc, char ** argv){
	//let's read in input substrings, and put them into a search tree of sorts
        substrNode inputString[26];

	for(int i = 0;i<26;i++){
		char newChar = (char) (97 + i);
		inputString[i] = substrNodeCreator(newChar); //this range represents all 26 lowercase letters 
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
