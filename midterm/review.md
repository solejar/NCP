

# C Functions



## Basic

`printf`

`strcmp(char * a, char * b)`: ***Care! Returns 0 for equality***

`#include <stdio.h>`

`#include <unistd.h>`

`#include <stdlib.h>`



Structs (in this case a linkedList node)

```c
typedef struct Name
{
	char * stringVal;
	int intVal;
	struct Name * next;
} Name
```



To iterate through chars in a string

```c
while(c!=NULL&& *c!='\0){ //the null terminated check only important for String library I think
	printf("%c\n",c*);
    c++;
}
```



Ways of defining string

```c
char * arr = calloc(1,sz+1); 
char *arr[sz+1];

if(arr) free(arr);
```

^Don't forget to free all new'ed or malloc'ed vars!

## I/O

`FILE* fopen(const char* pathname, const char*made)`

* return file pointer (to buffer)
* Mode
  * "r" - read only
  * "w" - write
  * "a" - append

`fclose(FILE* stream)`

`int fread(void *ptr, int size, int nmemb, FILE *stream)`

`int fwrite( void *ptr, int size, int nmemb, FILE * stream)`

`fgetc/fputc(char *str, FILE *stream) `

`fprintf(FILE * stream, char * str, char* info)` this is if you need string formatting

`fgets/fputs(char * str, int num, FILE *stream)`

`int fseek(FILE *fp, long offset, int whence)`

`long ftell(FILE *fp)`

`void rewind(FILE *fp)`



To tell the size of file, then read that in:

```c
fseek(fp, 0L, SEEK_END);
int sz = ftell(fp);
rewind(fp);

if(1!=fread(arr,sz,1,fp))
```



## Socket

`int socket(int domain, int type, int protocol)`

`int bind(int sockfd, struct sockaddr *my_addr, int addrlen)`

`int listen(int sockfd, int backlog)`

`int accept(int listenfd, struct sockaddr *addr, int *addrlen)`

`int connect(int sockfd, struct sockaddr *serv_addr, int addrlen)`

Week 5 - Server/Client:
	Server:
		#include <stdio.h>
		#include <sys/socket.h>
		#include <stdlib.h>
		#include <netinet/in.h>
		#include <string.h>
		#include <unistd.h>

		first initialize variables (serverfd, newsocket) (struct sockaddr_in address) (addrlen = sizeof(address));
		1. serverfd = socket (AF_INET, SOCK_STREAM, );
		2. address.sin_family = AF_INET, address.sin_addr.s_addr = INADDR_ANY, address.sin_port = htons(PORT);
		3. bind(server_fd, (struct sockaddr *)&address, sizeof(address))
		4. listen(serverfd, 1024);
		5. (new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))
		6. read/write from new socket.

	Client:
		#include <stdio.h>
		#include <sys/socket.h>
		#include <stdlib.h>
		#include <netinet/in.h>
		#include <string.h>
		#include <unistd.h>
		#include <arpa/inet.h>

		initialize vars again
		1. sock = socket(AF_INET, SOCK_STREAM, 0)
		2. memset(&serv_addr, '0', sizeof(serv_addr))
		3. serv_addr.sin_family = AF_INET; serv_addr.sin_port = htons(PORT);
		4. inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
		5. connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))
		6. read/write to sock

Week 6:
	Multiple Client Server:
		while(1){
	        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
	                       (socklen_t*)&addrlen))<0)
	        {
	            perror("accept");
	            exit(EXIT_FAILURE);
	        }
	        valread = read( new_socket , buffer, 1024);
	        printf("%s\n",buffer );
	        write(new_socket, response, strlen(response)); //response from server
	        printf("Response msg sent\n");
	        close(new_socket);
    	}

    readnbytes:
		ssize_t         /* Read "n" bytes from a descriptor. */
		readnbytes(int fd, void *vptr, size_t n) {
		    ssize_t nleft;
		    ssize_t nread;
		    char    *ptr;

		    ptr = vptr;
		    nleft = n;
		    while (nleft > 0) {
		        if ( (nread = read(fd, ptr, nleft)) < 0) { 
		            if (errno == EINTR){     /* Interrupted by signal handler*/
		                nread = 0;     /* and call read() again */
		                printf("Read Failure\n");
		            }
		            else
		                return(-1);
		        } else if (nread == 0)
		            break;              /* EOF */
		        nleft -= nread;
		        ptr   += nread;
		    }
		    return(n - nleft);      /* return >= 0 */
		}

	webserver:
		1. serveraddr.sin_port=htons(8080);
		2. 	for(;;) {
			    int clientfd;
			    if((clientfd=accept(sockfd, 0, 0)) < 0)
			      err_exit();
			    printf("Socket connected\n");
			    char response[]="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<HTML><BODY>Hello World!!!!!!!</BODY></HTML>\r\n";
			    if(write(clientfd, response, sizeof(response)) < 0)
			      err_exit();
			    printf("HTTP response sent\n");
			    close(clientfd);
  			}


Code to read in a request from the browser

```c
int listenfd, browserfd, port;
socklen_t clientlen;
struct sockaddr_in clientaddr;
char buffer[MAXLINE];

//assume port came from argv
listenfd = Open_listenfd(port);

while(1){
    clientlen = sizeof(clientaddr);     
    browserfd = Accept(listenfd, (SA *), &clientaddr, &clientlen);    
    bytesRead = read(browserfd, buffer, sizeof(buffer)); //this is blocking  
   
}

```



Code to make a request to a foreign server

```c
int serverfd = open_clientfd(reqHost, portno); //int port

if(write(serverfd,buffer,bytesRead)<0){
    perror("write");
    exit(-1);
}

int bytesRead = 0;
int lastRead = 0;

//while there is something left to read, read it and write it back to the browser
while((lastRead = read(serverfd,buffer,MAXLINE))>0){
    if(write(browserfd,buffer,lastRead)<0){
        perror("write");
        exit(-1);
    }
    
    bytesRead += lastRead;
}
```

## Threads/Processes

`int fork()`

- for parent, return is PID of child
- for child, return is 0

`exec()`

- p/v/e
  - p: search current execution path
  - v: accept arg list as vectory of pointers
  - e: an array of pointers to env vars is passed\

`exit(int returnCode)`: to tell how execution went

`pid_t wait(int *status)`

`pid_t waitpid(pid_t pis, int *status, int options)`

`extern char ** environ`



`int pthread_create(pthread_t *tid, pthread_attr_t *attr, func *f, void *arg)`

```
void * thread_handle(void *vargp){
    char buffer[1024] = {0};
    int connfd = *((int *)vargp);
    
    close(connfd); //gotta be careful to close this in the thread
}
```



`pthread_t pthread_self(void)` 

let's the new thread become selfaware



`void pthread_exit(void *thread_return)` usually just automatically called by return vals

`int pthread_join(pthread_t tid, void **thread_return)`: blocking

`int pthread_detach(pthread_t tid)` if you don't care about the results

# Psuedocode

# Linux

`strace touch x`: monitor system calls

`>` : redirect stdout to file

`<`: redirect stdin to file

`2>`: redirect stderr to file

`>>`: append stdout to file

`2>&1` redirect fd2 to fd1

`ifconfig lo`
